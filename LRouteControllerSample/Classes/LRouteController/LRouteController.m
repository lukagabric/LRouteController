#define kDirectionsURL @"http://maps.googleapis.com/maps/api/directions/json?"


#import "LRouteController.h"


@implementation LRouteController


- (void)getPolylineWithLocations:(NSArray *)locations andCompletitionBlock:(void (^)(GMSPolyline *polyline, NSError *error))completitionBlock
{
    [self getPolylineWithLocations:locations travelMode:TravelModeDriving andCompletitionBlock:completitionBlock];
}


- (void)getPolylineWithLocations:(NSArray *)locations travelMode:(TravelMode)travelMode andCompletitionBlock:(void (^)(GMSPolyline *polyline, NSError *error))completitionBlock
{
    NSUInteger locationsCount = [locations count];

    if (locationsCount < 2) return;
    
    if ([_request inProgress])
        [_request clearDelegatesAndCancel];
    
    NSMutableArray *locationStrings = [NSMutableArray new];

    for (CLLocation *location in locations)
    {
        [locationStrings addObject:[[NSString alloc] initWithFormat:@"%f,%f", location.coordinate.latitude, location.coordinate.longitude]];
    }
    
    NSString *sensor = @"false";
    NSString *origin = [locationStrings objectAtIndex:0];
    NSString *destination = [locationStrings lastObject];
    NSMutableString *url = [NSMutableString stringWithFormat:@"%@&origin=%@&destination=%@&sensor=%@", kDirectionsURL, origin, destination, sensor];
    
    if (locationsCount > 2)
    {
        [url appendString:@"&waypoints=optimize:false"];
        for (int i = 1; i < [locationStrings count] - 1; i++)
        {
            [url appendFormat:@"|%@", [locationStrings objectAtIndex:i]];
        }
    }
    
    switch (travelMode)
    {
        case TravelModeWalking:
            [url appendString:@"&mode=walking"];
            break;
        case TravelModeBicycling:
            [url appendString:@"&mode=bicycling"];
            break;
        case TravelModeTransit:
            [url appendString:@"&mode=transit"];
            break;
        default:
            [url appendString:@"&mode=driving"];
            break;
    }
    
    url = [NSMutableString stringWithString:[url stringByAddingPercentEscapesUsingEncoding:NSASCIIStringEncoding]];
    
    _request = [ASIHTTPRequest requestWithURL:[NSURL URLWithString:url] usingCache:nil andCachePolicy:ASIDoNotReadFromCacheCachePolicy | ASIDoNotWriteToCacheCachePolicy | ASIDontLoadCachePolicy];
    
    __weak ASIHTTPRequest *weakRequest = _request;
    
    [_request setCompletionBlock:^{
        NSError *error;
        NSDictionary *json = [NSJSONSerialization JSONObjectWithData:weakRequest.responseData options:kNilOptions error:&error];

        if (!error)
        {
            NSArray *routesArray = [json objectForKey:@"routes"];
            
            if ([routesArray count] > 0)
            {
                NSDictionary *routeDict = [routesArray objectAtIndex:0];
                NSDictionary *routeOverviewPolyline = [routeDict objectForKey:@"overview_polyline"];
                NSString *points = [routeOverviewPolyline objectForKey:@"points"];
                GMSPath *path = [GMSPath pathFromEncodedPath:points];
                GMSPolyline *polyline = [GMSPolyline polylineWithPath:path];
                completitionBlock(polyline, nil);
            }
            else
            {
#if DEBUG
                if (locationsCount > 10)
                    NSLog(@"If you're using Google API's free service you will not get the route. Free service supports up to 8 waypoints + origin + destination.");
#endif
                completitionBlock(nil, nil);
            }
        }
        else
        {
            completitionBlock(nil, error);
        }
    }];
    
    [_request setFailedBlock:^{
        completitionBlock(nil, weakRequest.error);
    }];
    
    [_request startAsynchronous];
}


- (void)abortRequest
{
    if (_request && [_request inProgress])
        [_request clearDelegatesAndCancel];
}


- (void)dealloc
{
    [self abortRequest];
}


@end
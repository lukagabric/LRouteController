#import "MapViewController.h"


@implementation MapViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _coordinates = [NSMutableArray new];
    _routeController = [LRouteController new];
    
    GMSCameraPosition *camera = [GMSCameraPosition cameraWithLatitude:45.55 longitude:18.69 zoom:12];
    _mapView = [GMSMapView mapWithFrame:self.view.bounds camera:camera];
    _mapView.myLocationEnabled = YES;
    _mapView.delegate = self;
    [self.view addSubview:_mapView];
    
    _markerStart = [GMSMarker new];
    _markerStart.title = @"Start";
    
    _markerFinish = [GMSMarker new];
    _markerFinish.title = @"Finish";
}


#pragma mark - GMSMapViewDelegate


- (void)mapView:(GMSMapView *)mapView didTapAtCoordinate:(CLLocationCoordinate2D)coordinate
{
    _polyline.map = nil;
    _markerStart.map = nil;
    _markerFinish.map = nil;
    
    [_coordinates addObject:[[CLLocation alloc] initWithLatitude:coordinate.latitude longitude:coordinate.longitude]];
    
    if ([_coordinates count] > 1)
    {
        [_routeController getPolylineWithLocations:_coordinates travelMode:TravelModeDriving andCompletitionBlock:^(GMSPolyline *polyline, NSError *error) {
            if (error)
            {
                NSLog(@"%@", error);
            }
            else if (!polyline)
            {
                NSLog(@"No route");
                [_coordinates removeAllObjects];
            }
            else
            {
                _markerStart.position = [[_coordinates objectAtIndex:0] coordinate];
                _markerStart.map = _mapView;
                
                _markerFinish.position = [[_coordinates lastObject] coordinate];
                _markerFinish.map = _mapView;
                
                _polyline = polyline;
                _polyline.strokeWidth = 3;
                _polyline.strokeColor = [UIColor blueColor];
                _polyline.map = _mapView;
            }
        }];
    }
}


#pragma mark -


@end
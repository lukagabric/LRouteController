#import <Foundation/Foundation.h>
#import <GoogleMaps/GoogleMaps.h>
#import "ASIHTTPRequest.h"


typedef enum tagTravelMode
{
    TravelModeDriving,
    TravelModeBicycling,
    TravelModeTransit,
    TravelModeWalking
}TravelMode;


@interface LRouteController : NSObject
{
    ASIHTTPRequest *_request;
}


- (void)getPolylineWithLocations:(NSArray *)locations travelMode:(TravelMode)travelMode andCompletitionBlock:(void (^)(GMSPolyline *polyline, NSError *error))completitionBlock;
- (void)getPolylineWithLocations:(NSArray *)locations andCompletitionBlock:(void (^)(GMSPolyline *polyline, NSError *error))completitionBlock;
- (void)abortRequest;


@end
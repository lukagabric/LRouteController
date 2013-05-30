#import <GoogleMaps/GoogleMaps.h>
#import "LRouteController.h"


@interface MapViewController : UIViewController <GMSMapViewDelegate>
{
    NSMutableArray *_coordinates;
    __weak GMSMapView *_mapView;
    LRouteController *_routeController;
    GMSPolyline *_polyline;
    GMSMarker *_markerStart;
    GMSMarker *_markerFinish;
}


@end
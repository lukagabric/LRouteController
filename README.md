LRouteController
================

Simple class to get and draw route with optional waypoints using Google Maps SDK for iOS

Usage:

    //_coordinates - array of CLLocation objects (first - start; last - finish; rest - waypoints)
    [_routeController getPolylineWithLocations:_coordinates travelMode:TravelModeWalking andCompletitionBlock:^(GMSPolyline *polyline, NSError *error) {
        polyline.map = _mapView;
    }];

Screenshot:

[![](http://lukagabric.com/wp-content/uploads/2013/05/LRouteControllerSample.png)](http://lukagabric.com/wp-content/uploads/2013/05/LRouteControllerSample.png)

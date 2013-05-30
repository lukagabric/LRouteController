LRouteController
================

Simple class to get and draw route with optional waypoints using Google Maps SDK for iOS.

Through Google Directions API route points are received and encoded into GMSPath objects. Using GMSPath object a GMSPolyline object is created. GMSMapView may be assigned to a GMSPolyline object and the route is drawn on a map. To make the process as simple as possible I’ve created the LRouteController class.

Usage
-----

    //_coordinates - array of CLLocation objects (first - start; last - finish; rest - waypoints)
    [_routeController getPolylineWithLocations:_coordinates travelMode:TravelModeWalking andCompletitionBlock:^(GMSPolyline *polyline, NSError *error) {
        polyline.map = _mapView;
    }];

Check the sample application for more info.

Screenshot
----------

[![](http://lukagabric.com/wp-content/uploads/2013/05/LRouteControllerSample.png)](http://lukagabric.com/wp-content/uploads/2013/05/LRouteControllerSample.png)

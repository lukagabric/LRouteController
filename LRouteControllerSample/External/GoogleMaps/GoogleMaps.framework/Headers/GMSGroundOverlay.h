//
//  GMSGroundOverlay.h
//  Google Maps SDK for iOS
//
//  Copyright 2013 Google Inc.
//
//  Usage of this SDK is subject to the Google Maps/Google Earth APIs Terms of
//  Service: https://developers.google.com/maps/terms
//

#import <GoogleMaps/GMSOverlay.h>

@class GMSCoordinateBounds;

/**
 * GMSGroundOverlay specifies the available options for a ground overlay that
 * exists on the Earth's surface. Unlike a marker, the position of a ground
 * overlay is specified explicitly and it does not face the camera.
 */
@interface GMSGroundOverlay : GMSOverlay

/**
 * The position of this ground overlay, or more specifically, the physical
 * position of its anchor.
 * If bounds has been specified, it will be updated to reflect the move to the
 * new position.
 */
@property (nonatomic, assign) CLLocationCoordinate2D position;

/**
 * As groundAnchor on GMSMarker. Specifies where the ground overlay is anchored
 * to the earth in relation to its position.
 * If bounds has been specified, position will be updated to keep the overlay
 * within the bounds.
 */
@property (nonatomic, assign) CGPoint anchor;

/**
 * Icon to render on the earth. Unlike for GMSMarker, this is required.
 */
@property (nonatomic, strong) UIImage *icon;

/**
 * The zoom level at which this ground overlay is displayed at 1:1. Will be
 * clamped to ensure that it is at least 0.
 * If bounds has been specified, it will be updated to fit the image at the new
 * zoomLevel.
 * zoomLevel will be updated when setting a new bounds or icon.
 */
@property (nonatomic, assign) CGFloat zoomLevel;

/**
 * Bearing of this ground overlay, in degrees. The default value, zero, points
 * this ground overlay up/down along the normal Y axis of the earth.
 */
@property (nonatomic, assign) CLLocationDirection bearing;

/**
 * The bounds within which the overlay fits, ignoring the bearing. Overlay is
 * scaled to fit within these bounds.
 * Setting this will adjust the position accordingly.
 */
@property (nonatomic, strong) GMSCoordinateBounds *bounds;

/**
 * Convenience constructor for GMSGroundOverlay for a particular position and
 * icon. Other properties will have default values.
 */
+ (instancetype)groundOverlayWithPosition:(CLLocationCoordinate2D)position
                                     icon:(UIImage *)icon;
/**
 * Convenience constructor for GMSGroundOverlay for a particular bounds and
 * icon. Will set position accordingly.
 */
+ (instancetype)groundOverlayWithBounds:(GMSCoordinateBounds *)bounds
                                   icon:(UIImage *)icon;


@end

/**
 * The default position of the ground anchor of a GMSGroundOverlay: the center
 * point of the icon.
 */
FOUNDATION_EXTERN const CGPoint kGMSGroundOverlayDefaultAnchor;

/** The default zoom level this ground overlay is displayed at. */
FOUNDATION_EXTERN const CGFloat kGMSGroundOverlayDefaultZoom;

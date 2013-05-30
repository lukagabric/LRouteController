//
//  GMSTileLayer.h
//  Google Maps SDK for iOS
//
//  Copyright 2013 Google Inc.
//
//  Usage of this SDK is subject to the Google Maps/Google Earth APIs Terms of
//  Service: https://developers.google.com/maps/terms
//

@class GMSMapView;

/**
 * Stub tile that is used to indicate that no tile exists for a specific tile
 * coordinate. May be returned by tileForX:y:zoom: on GMSTileProvider.
 */
FOUNDATION_EXTERN UIImage *const kGMSTileLayerNoTile;

/**
 * GMSTileReceiver is provided to GMSTileLayer when a tile request is made,
 * allowing the callback to be later (or immediately) invoked.
 */
@protocol GMSTileReceiver<NSObject>
- (void)receiveTileWithX:(NSUInteger)x
                       y:(NSUInteger)y
                    zoom:(NSUInteger)zoom
                   image:(UIImage *)image;
@end

/*
 * GMSTileLayer is an abstract class that allows overlaying of custom image
 * tiles on a specified GMSMapView. It may not be initialized directly, and
 * subclasses must implement the tileForX:y:zoom: method to return tiles.
 *
 * At zoom level 0 the whole world is a square covered by a single tile,
 * and the coordinates |x| and |y| are both 0 for that tile. At zoom level 1,
 * the world is covered by 4 tiles with |x| and |y| being 0 or 1, and so on.
 * The size of a tile is 256x256 points.
 */
@interface GMSTileLayer : NSObject

/**
 * requestTileForX:y:zoom:receiver: generates image tiles for GMSTileOverlay.
 * It must be overridden by subclasses. The tile for the given |x|, |y| and
 * |zoom| _must_ be later passed to |receiver|.
 *
 * Specify kGMSTileLayerNoTile if no tile is available for this location; or
 * nil if a transient error occured and a tile may be available later. If the
 * specified UIImage is not 256x256 points, it is shrinked/enlarged to 256x256.
 *
 * Calls to this method will be made on the main thread. See GMSSyncTileLayer
 * for a base class that implements a blocking tile layer that does not run on
 * your application's main thread.
 */
- (void)requestTileForX:(NSUInteger)x
                      y:(NSUInteger)y
                   zoom:(NSUInteger)zoom
               receiver:(id<GMSTileReceiver>)receiver;

/**
 * Clears the cache so that all tiles will be requested again.
 */
- (void)clearTileCache;

/**
 * The map this GMSTileOverlay is displayed on. Setting this property will add
 * the layer to the map. Setting it to nil removes this layer from the map. A
 * layer may be active on at most one map at any given time.
 */
@property (nonatomic, weak) GMSMapView *map;

/**
 * Higher |zIndex| value tile layers will be drawn on top of lower |zIndex|
 * value tile layers.  Equal values result in undefined draw ordering.
 */
@property (nonatomic, assign) NSUInteger zIndex;

@end

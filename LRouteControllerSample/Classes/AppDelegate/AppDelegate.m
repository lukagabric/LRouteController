#import "AppDelegate.h"
#import "MapViewController.h"
#import <GoogleMaps/GoogleMaps.h>


NSString * const NSURLIsExcludedFromBackupKey = @"NSURLIsExcludedFromBackupKey";


@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [GMSServices provideAPIKey:@"AIzaSyBL5wLVeEmnveYO2EhDZcwiBU6Nk_eP3vA"];

    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.rootViewController = [MapViewController new];
    [self.window makeKeyAndVisible];
    return YES;
}


@end
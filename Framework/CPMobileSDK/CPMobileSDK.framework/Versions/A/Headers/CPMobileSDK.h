//
//  CPMobileSDK.h
//  CPMobileSDK
//
//  Created by Leo Natan.
//  Copyright © 2016 Check Point Software Technologies. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <CPMobileSDK/CPSecureUserDefaults.h>
#import <CPMobileSDK/CPSecurePasteboard.h>
#import <CPMobileSDK/CPSecureDocumentInteractionController.h>
#import <CPMobileSDK/CPSecureValueTransformer.h>
#import <CPMobileSDK/CPSecureFetchRequest.h>
#import <CPMobileSDK/NSManagedObjectContext+CPSecureCoreData.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark Constants

/**
 Posted when user taps the "Try Without Capsule Workspace" button. Only applicable if @c CPMobileSDKOptions.allowAppUsageWithoutCapsuleIntegration is enabled.
 */
extern NSString* const CPMobileSDKDisableSecurityNotification;
/**
 Posted when the encryption key becomes available, once the user has authenticated with Capsule Workspace.
 */
extern NSString* const CPMobileSDKEncryptionKeyAvailableNotification;
/**
 Posted when the encryption key becomes unavailable, usually if user has logged out in Capsule Workspace, or some other issue has come up and requires the user's reauthentication.
 */
extern NSString* const CPMobileSDKEncryptionKeyUnavailableNotification;
/**
 Posted when the application is unlocked.
 */
extern NSString* const CPMobileSDKDidUnlockApplicationNotification;
/**
 Posted when the application is locked.
 */
extern NSString* const CPMobileSDKDidLockApplicationNotification;
/**
 A key whose value is a @c NSData object representing the encryption key for the application. This key is used with @c CPMobileSDKEncryptionKeyAvailableNotification notifications.
 */
extern NSString* const CPMobileSDKEncryptionKeyUserInfoKey;
/**
 The version of the SDK.
 */
extern NSString* const CPMobileSDKVersion;

#pragma mark CPMobileSDK Options

/**
 A @c CPMobileSDKOptions object defines the behavior and policies to use when starting the mobile SDK.
 */
@interface CPMobileSDKOptions : NSObject

/**
 Displays a button allowing users to disable the mobile SDK and use the application without security or integration with Capsule Workspace.
 
 Defaults to @c false.
 */
@property (nonatomic, assign) BOOL allowAppUsageWithoutCapsuleIntegration;

/**
 Controls whether mobile policy is enforced on system actions, such as pasteboard copy-paste, document interactions, etc.
 
 When set to @c false, system actions, such as copy-paste will be performed normally, without policy enforment. It is up to the developer to ensure no data leaks.
 
 Defaults to @c true.
 */
@property (nonatomic, assign) BOOL enforceMobilePolicyOnSystem;

@end

#pragma mark CPMobileSDKApplicationMain

/**
 This is a convenience function for quick integration with the SDK. Call this function in your @c main function instead of @c UIApplicationMain.
 
 
 The function is called in the main entry point to create the application object and the application delegate and set up the event cycle. Internally, @c CPMobileSDK.startSDKWithOptions(_:) is called to start the SDK with the provided options. Once the system is ready and the user has unlocked the application, the application delegate will start receiving normal application life cycle method calls.

 @param argc               The count of arguments in @c argv; this usually is the corresponding parameter to @c main.
 @param argv               A variable list of arguments; this usually is the corresponding parameter to @c main.
 @param principalClassName The name of the @c UIApplication class or subclass. If you specify @c nil, the value for @c NSPrincipalClass from the Info.plist is used. If there is no @c NSPrincipalClass key specified, the @c UIApplication class is used.
 @param delegateClassName  The name of the class from which the application delegate is instantiated. If @c principalClassName designates a subclass of @c UIApplication, you may designate the subclass as the delegate; the subclass instance receives the application-delegate messages. Specify @c nil if you load the delegate object from your application’s main nib file. The delegate class will be instantiated using @c init.
 @param SDKOptions         An options object, defining the behavior of the mobile SDK.
 
 @return Even though an integer return type is specified, this function never returns.
 */
int CPMobileSDKApplicationMain(int argc, char *argv[], NSString * __nullable principalClassName, NSString * __nullable delegateClassName,  CPMobileSDKOptions* __nullable SDKOptions);

#pragma mark CPMobileSDK

/**
 The main Check Point Mobile SDK class. Use this class' methods to start the mobile SDK, pass URLs to the SDK and obtain the application encryption key.
 
 Before starting the SDK, add observers for at least @c CPMobileSDKEncryptionKeyAvailableNotification and @c CPMobileSDKDidUnlockApplicationNotification. Start the SDK by calling @c CPMobileSDK.startSDKWithOptions(_:) like so:
 
 @code
 func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
	// Override point for customization after application launch.
	NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(AppDelegate.mobileSDKEncryptionKeyAvailable(_:)), name: CPMobileSDKEncryptionKeyAvailableNotification, object: nil)
	NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(AppDelegate.mobileSDKDidUnlockApplication(_:)), name: CPMobileSDKDidUnlockApplicationNotification, object: nil)
 
	CPMobileSDK.startSDKWithOptions(nil)
 
	return true
 }
 
 internal func mobileSDKEncryptionKeyAvailable(note: NSNotification) {
	if let encryptionKey = note.userInfo?[CPMobileSDKEncryptionKeyUserInfoKey] as? NSData {
		//Use encryption key to start I/O related API.
	}
 }
 
 internal func mobileSDKDidUnlockApplication(note: NSNotification) {
	//Present the app's UI here if not already presented.
 }
 @endcode
 
 UI can be presented before the application is unlocked by the SDK, but this may cause unexpected results, such as starting network requests or disk access. It is best to present the UI only once the application is first unlocked. For projects which start their UI in code, this is very simple – move the UI code to the @c CPMobileSDKDidUnlockApplicationNotification observer method. For UI loaded from a Storyboard or a NIB/XIB, the simplest solution is to introduce a landing view controller, and present the real UI in the @c CPMobileSDKDidUnlockApplicationNotification observer method. The included demo project demonstrates how to achieve this.
 
 Once the application is locked, it is generally safe to operate the UI normally, even if hidden. However, it is advised to close all work and discard the UI once a @c CPMobileSDKEncryptionKeyUnavailableNotification notification is posted.
 */
@interface CPMobileSDK : NSObject

#pragma mark Starting the SDK

/**
 Call this method to initialize the SDK. Usually, you should call this method in @c UIApplicationDelegate.application(_:didFinishLaunchingWithOptions:).
 
 @param options An options object, defining the behavior of the mobile SDK.
 */
+ (void)startSDKWithOptions:(nullable CPMobileSDKOptions*)options;

#pragma mark URL Handling

/**
 Call this in @c UIApplicationDelegate.application(_:openURL:options:) method to handle SDK-related URLs.
 
 @param url     The URL resource to handle.
 @param options A dictionary of launch options.
 
 @return Returns @c true if handled by SDK, @c false if URL is unrelated to SDK and should be handled by the application.
 */
+ (BOOL)handleSDKOpenURL:(NSURL *)url options:(NSDictionary<NSString*, id> *)options;

/**
 Call this in @c UIApplicationDelegate.application(_:sourceApplication:annotation:) method to handle SDK-related URLs.
 
 @param url               The URL resource to handle.
 @param sourceApplication The bundle ID of the app that is requesting your app to open the URL (url).
 @param annotation        A property list object supplied by the source app to communicate information to the receiving app.
 
 @return Returns @c true if handled by SDK, @c false if URL is unrelated to SDK and should be handled by the application.
 */
+ (BOOL)handleSDKOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation NS_DEPRECATED_IOS(2_0, 9_0, "Use CPMobileSDK.handleSDKOpenURL(_:options:)");

#pragma mark Encryption Key

/**
 The encryption key for the application. To listen when this key becomes available and unavailable, register to @c CPMobileSDKEncryptionKeyAvailableNotification and @c CPMobileSDKEncryptionKeyUnavailableNotification notifications.
 
 @return The application encryption key, if available, otherwise returns @c nil.
 */
+ (nullable NSData*)encryptionKey;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark Tint Colors

@interface CPMobileSDK (TintColor)

/**
 The default tint color, for style similar to Capsule Workspace.
 
 @return The default tint color.
 */
+ (UIColor*)defaultAppTintColor;
/**
 The default accent color, for style similar to Capsule Workspace.
 
 @return The default accent color.
 */
+ (UIColor*)defaultAccentTintColor;

@end

NS_ASSUME_NONNULL_END
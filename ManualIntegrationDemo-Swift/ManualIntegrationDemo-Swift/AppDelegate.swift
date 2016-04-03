//
//  AppDelegate.swift
//  ManualIntegrationDemo-Swift
//
//  Created by Leo Natan on 2016-03-06.
//  Copyright © 2016 checkpoint. All rights reserved.
//

import UIKit
import CPMobileSDK

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
	
	private var didStartUIAfterFrameworkReady : Bool = false

	var window: UIWindow?

	func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
		NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(AppDelegate.mobileSDKEncryptionKeyAvailable(_:)), name: CPMobileSDKEncryptionKeyAvailableNotification, object: nil)
		NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(AppDelegate.mobileSDKDidUnlockApplication(_:)), name: CPMobileSDKDidUnlockApplicationNotification, object: nil)
		NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(AppDelegate.mobileSDKDidUnlockApplication(_:)), name: CPMobileSDKDisableSecurityNotification, object: nil)
		
		let options = CPMobileSDKOptions()
		options.allowAppUsageWithoutCapsuleIntegration = true
		
		CPMobileSDK.startSDKWithOptions(options)
		
		return true
	}
	
	func applicationWillResignActive(application: UIApplication) {
		// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
		// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
	}

	func applicationDidEnterBackground(application: UIApplication) {
		// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
		// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
	}

	func applicationWillEnterForeground(application: UIApplication) {
		// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
	}

	func applicationDidBecomeActive(application: UIApplication) {
		// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
	}

	func applicationWillTerminate(application: UIApplication) {
		// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
	}
	
	//MARK: CPMobileSDK Handling
	
	internal func mobileSDKEncryptionKeyAvailable(note: NSNotification) {
		if let encryptionKey = note.userInfo?[CPMobileSDKEncryptionKeyUserInfoKey] as? NSData {
			//Use encryption key to start I/O related API.
			print("Got encryption key: \(encryptionKey)")
		}
	}
	
	internal func mobileSDKDidUnlockApplication(note: NSNotification) {
		//Present the app's UI here if not already presented.
		if !didStartUIAfterFrameworkReady {
			self.window?.rootViewController?.performSegueWithIdentifier("SDKIsReadyIdentifier", sender: nil)
			didStartUIAfterFrameworkReady = true
		}
	}
}


//
//  main.swift
//  SecureCoreDataDemo-Swift
//
//  Created by Leo Natan on 2016-04-03.
//  Copyright © 2016 checkpoint. All rights reserved.
//

import CPMobileSDK

let options = CPMobileSDKOptions()
options.allowAppUsageWithoutCapsuleIntegration = false
CPMobileSDKApplicationMain(Process.argc, Process.unsafeArgv, nil, NSStringFromClass(AppDelegate), options)
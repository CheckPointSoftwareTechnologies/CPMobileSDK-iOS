//
//  ViewController.swift
//  SecureCoreDataDemo-Swift
//
//  Created by Leo Natan on 2016-03-08.
//  Copyright © 2016 checkpoint. All rights reserved.
//

import UIKit
import CPMobileSDK

class ViewController: UIViewController {

	override func viewDidLoad() {
		super.viewDidLoad()
		// Do any additional setup after loading the view, typically from a nib.
	}

	override func didReceiveMemoryWarning() {
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}
	
	var appDelegate : AppDelegate {
		get {
			return UIApplication.sharedApplication().delegate as! AppDelegate
		}
	}

	@IBAction func addObjects(sender: AnyObject) {
		for idx in 1...10 {
			let obj = NSEntityDescription.insertNewObjectForEntityForName("Entity", inManagedObjectContext: appDelegate.managedObjectContext) as! Entity
			
			obj.integerProperty = Int64(idx)
			obj.secureIntegerProperty = NSNumber(longLong: Int64(idx))
			
			obj.clearStringProperty = "This string is clean \(idx)"
			obj.secureStringProperty = "This string is encrypted \(idx)"
		}
		
		do {
			try appDelegate.managedObjectContext.save()
		}
		catch let e as NSError {
			print("Error saving: \(e)")
		}
	}
	
	@IBAction func performFetch(sender: AnyObject) {
		let secureFetchRequest = CPSecureFetchRequest(entityName: "Entity")
		secureFetchRequest.predicate = NSPredicate(format: "integerProperty >= 5")
		secureFetchRequest.securePredicate = NSPredicate(format: "secureStringProperty CONTAINS '7'")
		
		do {
			let results = try appDelegate.managedObjectContext.executeSecureFetchRequest(secureFetchRequest)
			
			print("Got \(results.count) results")
		}
		catch let e as NSError {
			print("Error fetching: \(e)")
		}
	}
	
}


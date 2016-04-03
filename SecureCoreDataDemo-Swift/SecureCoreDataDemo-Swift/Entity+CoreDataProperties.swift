//
//  Entity+CoreDataProperties.swift
//  SecureCoreDataDemo-Swift
//
//  Created by Leo Natan on 2016-04-03.
//  Copyright © 2016 checkpoint. All rights reserved.
//
//  Choose "Create NSManagedObject Subclass…" from the Core Data editor menu
//  to delete and recreate this implementation file for your updated model.
//

import Foundation
import CoreData

extension Entity {

    @NSManaged var clearStringProperty: String?
    @NSManaged var integerProperty: Int64
    @NSManaged var secureStringProperty: String?
    @NSManaged var secureIntegerProperty: NSNumber

}

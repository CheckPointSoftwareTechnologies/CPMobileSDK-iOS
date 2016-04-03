//
//  CPSecureFetchRequest.h
//  CPMobileSDK
//
//  Created by Leo Natan.
//  Copyright © 2016 Check Point Software Technologies. All rights reserved.
//

#import <CoreData/CoreData.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A subclass of @c NSFetchRequest for performing searches with predicates referencing secure properties.
 
 Secure fetch requests contain two predicates; @c predicate for constraining non-secure properties, and @c securePredicate, for constraining secure properties.
 
 @code
 let secureFetchRequest = CPSecureFetchRequest(entityName: "Entity")
 secureFetchRequest.predicate = NSPredicate(format: "integerProperty >= 5")
 secureFetchRequest.securePredicate = NSPredicate(format: "secureStringProperty CONTAINS '7'")
 @endcode
 */
@interface CPSecureFetchRequest : NSFetchRequest

/**
 The predicate is used to constrain the selection of objects the receiver is to fetch. For more about predicates, see Predicate Programming Guide.

 Use this predicate to constrain secure properties (properties transformed using @c CPSecureValueTransformer and subclasses).
 
 @Note While you can use this property to constrain all properties of your objects, it is not recommended. For performance reasons, make sure to constraints all non-secure properties using @c predicate, and only constrain secure properties using @c securePredicate.
 */
@property (nullable, nonatomic, strong) NSPredicate *securePredicate;

@end

NS_ASSUME_NONNULL_END
//
//  NSManagedObjectContext+CPSecureCoreData.h
//  CPMobileSDK
//
//  Created by Leo Natan.
//  Copyright © 2016 Check Point Software Technologies. All rights reserved.
//

#import <CoreData/CoreData.h>

@class CPSecureFetchRequest;

NS_ASSUME_NONNULL_BEGIN

/**
 Additions for executing secure fetch requests.
 
 In order to secure Core Data attributes, change the attribute type to transformable, and set the transformer name to @c CPSecureValueTransformer or a subclass of @c CPSecureValueTransformer.
 
 Properties set to be transformed with @c CPSecureValueTransformer and subclasses will be stored securely in Core Data stores.
 
 Since attributes are securely transformed into encrypted values, executing normal fetch requests will result in an undefined behavior, and will not return correct results. Instead, use @c CPSecureFetchRequest objects to create secure fetch requests, and execute using @c NSManagedObject.executeSecureFetchRequest(_:).
 */
@interface NSManagedObjectContext (CPSecureCoreData)

/**
 Returns an array of objects that meet the criteria specified by a given secure fetch request.
 
 An array of objects that meet the criteria specified by request fetched from the receiver and from the persistent stores associated with the receiver’s persistent store coordinator. If an error occurs, returns @c nil. If no objects match the criteria specified by request, returns an empty array.
 
 @param request A secure fetch request that specifies the search criteria for the fetch.
 @param error   If there is a problem executing the fetch, upon return contains an instance of @c NSError that describes the problem.
 
 @return An array of objects that meet the criteria specified by request fetched from the receiver and from the persistent stores associated with the receiver’s persistent store coordinator.
 */
- (nullable NSArray *)executeSecureFetchRequest:(CPSecureFetchRequest *)request error:(NSError * __autoreleasing * __nullable)error;

/**
 Returns the number of objects a given secure fetch request would have returned if it had been passed to @c executeSecureFetchRequest(_:).
 
 The number of objects a given fetch request would have returned if it had been passed to @c executeSecureFetchRequest(_:), or @c NSNotFound if an error occurs.
 
 @param request A secure fetch request that specifies the search criteria for the fetch.
 @param error   If there is a problem executing the fetch, upon return contains an instance of @c NSError that describes the problem.
 
 @return The number of objects a given fetch request would have returned if it had been passed to @c executeSecureFetchRequest(_:), or @c NSNotFound if an error occurs.
 */
- (NSUInteger)countForSecureFetchRequest:(CPSecureFetchRequest *)request error: (NSError * __autoreleasing * __nullable)error;

@end

NS_ASSUME_NONNULL_END
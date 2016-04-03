//
//  CPSecureValueTransformer.h
//  CPMobileSDK
//
//  Created by Leo Natan.
//  Copyright © 2016 Check Point Software Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A secure subclass of @c NSValueTransformer, for use with Core Data models. Instances of @c CPSecureValueTransformer are used to transform Core Data types to and from encrypted binary data in Core Data stores.
 
 When subclassing, make sure to call the super implementation of @c transformedValue(_:) and @c reverseTransformedValue(_:).
 */
@interface CPSecureValueTransformer : NSValueTransformer

/**
 Sets the encryption key to use with @c CPSecureValueTransformer instances. Setting the encryption key to @c nil will cause instances of @c CPSecureValueTransformer to transform values in clear.
 
 @param encryptionKey The encryption key to use with @c CPSecureValueTransformer instances.
 */
+ (void)setEncryptionKey:(nullable NSData*)encryptionKey;

@end

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

#import <Foundation/Foundation.h>
#import "alljoyn/controlpanel/LanguageSet.h"

/**
 * AJCPSLanguageSet is used to define a LanguageSet
 */
@interface AJCPSLanguageSet : NSObject

- (id)initWithHandle:(ajn ::services ::LanguageSet *)handle;


/**
 * Get the LanguageSetName
 * @return LanguageSetName
 */
- (NSString *)getLanguageSetName;

/**
 * Get the number of Languages defined
 * @return number of Languages
 */
- (size_t)getNumLanguages;

/**
 * Add a language to the LanguageSet
 * @param language - language to Add
 */
- (void)addLanguage:(NSString *)language;

/**
 *
 * Get the Languages defined in the LanguageSet
 * @return languages vector
 */
//const std::vector<qcc::String>&
- (NSArray *)getLanguages;


@end

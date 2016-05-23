////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "AJNSessionOptions.h"
#import "AJNObject.h"
#import "AJNBusObject.h"
#import "AJNStatus.h"
#import "AJNAboutDataListener.h"
#import "AJNMessageArgument.h"


@interface AJNAboutObjectDescription : AJNObject


/**
 * Fill in the ObjectDescription fields using a MsgArg
 *
 * The MsgArg must contain an array of type a(oas) The expected use of this
 * class is to fill in the ObjectDescription using a MsgArg obtain from the Announce
 * signal or the GetObjectDescription method from org.alljoyn.About interface.
 *
 * If the arg came from the org.alljoyn.About.Announce signal or the
 * org.alljoyn.AboutGetObjectDescrption method then it can be used to create
 * the AboutObjectDescription. If the arg came from any other source its best
 * to create an empty AboutObjectDescrption class and use the CreateFromMsgArg
 * class to access the MsgArg. Since it can be checked for errors while parsing
 * the MsgArg.
 *
 * @param arg MsgArg contain About ObjectDescription
 */
- (id)initWithMsgArg:(AJNMessageArgument *)msgArg;

/**
 * Fill in the ObjectDescription fields using a MsgArg
 *
 * The MsgArg must contain an array of type a(oas) The expected use of this
 * class is to fill in the ObjectDescription using a MsgArg obtain from the Announce
 * signal or the GetObjectDescription method from org.alljoyn.about interface.
 *
 * @param arg MsgArg contain AboutData dictionary
 *
 * @return ER_OK on success
 */
- (QStatus)createFromMsgArg:(AJNMessageArgument *)msgArg;

/**
 * Get a list of the paths that are added to this AboutObjectDescription.
 *
 * usage example
 * @code
 * size_t numPaths = [aboutObjectDescription getPaths:nil withSize:0];
 * NSMutableArray *paths = [[NSMutableArray alloc] initWithCapacity:numPaths];
 * [aboutObjectDescription getPaths:&paths withSize:numPaths]
 * @endcode
 *
 * @param[out] paths a pointer to NSMutableArray containing the paths
 * @param[in]  numPaths the size of the char* array
 *
 * @return
 *    The total number of paths found in the AboutObjectDescription.  If this
 *    number is larger than `numPaths` then only `numPaths` of paths will be
 *    returned in the `paths` array.
 *
 */
- (size_t)getPaths:(NSMutableArray **)path withSize:(size_t)numOfPaths;

/**
 * Get a list of interfaces advertised at the given path that are part of
 * this AboutObjectDescription.
 *
 * usage example
 * @code
 * size_t numInterfaces = [aboutObjectDescription getInterfacesForPath:@"/basic_object" interfaces:nil numOfInterfaces:0];
 * NSMutableArray *interfacePaths = [[NSMutableArray alloc] initWithCapacity:numPaths];
 * [aboutObjectDescription getInterfacePathsForInterface:@"com.alljoyn.example" paths:&interfacePaths numOfPaths:numInterfaces]
 * @endcode
 *
 * @param[in]  path the path we want to get a list of interfaces for
 * @param[out] interfaces a pointer to NSMututableArray containing the list of interfaces
 * @param[in]  numInterfaces the size of the char* array
 *
 * @return
 *    The total number of interfaces found in the AboutObjectDescription for
 *    the specified path.  If this number is larger than `numInterfaces`
 *    then only `numInterfaces` of interfaces will be returned in the
 *    `interfaces` array.
 */
- (size_t)getInterfacesForPath:(NSString *)path interfaces:(NSMutableArray **)interfaces numOfInterfaces:(size_t)numOfInterfaces;

/**
 * Get a list of the paths for a given interface. Its possible to have the
 * same interface listed under multiple paths.
 *
 * Usage example
 * @code
 * size_t numPaths = [aboutObjectDescription getInterfacePathsForInterface:@"com.alljoyn.example" paths:nil numOfPaths:0];
 * NSMutableArray *interfacePaths = [[NSMutableArray alloc] initWithCapacity:numPaths];
 * [aboutObjectDescription getInterfacePathsForInterface:@"org.alljoyn.example" paths:&interfacePaths numOfPaths:numPaths]
 * @endcode
 *
 * @param[in]  interface the interface we want to get a list of paths for
 * @param[out] paths a pointer to NSMutableArray containing the interfaces
 * @param[in]  numPaths the size of the char* array
 *
 * @return
 *    The total number of paths found in the AboutObjectDescription for
 *    the specified path.  If this number it larger than the `numPaths`
 *    then only `numPaths` of interfaces will be returned in the `paths`
 *    array
 *
 */
- (size_t)getInterfacePathsForInterface:(NSString *)interface paths:(NSMutableArray **)paths numOfPaths:(size_t)numOfPaths;

/**
 * Clear all the contents of this AboutObjectDescription
 *
 * @return ER_OK
 */
- (void)clear;

/**
 * Returns true if the given path is found
 *
 * @param[in] path BusObject path
 *
 * @return true if the path is found
 */
- (BOOL)hasPath:(const char *)path;

/**
 * Returns true if the given interface name is found in any path
 *
 * @param[in] interfaceName the name of the interface you are looking for
 *
 * @return true if the interface is found
 */
- (BOOL)hasInterface:(const char *)interface;

/**
 * Returns true if the given interface name is found at the given path
 * @param[in] path of the interface
 * @param[in] interfaceName the name of the interface you are looking for
 *
 * @return true if the interface is found at the given path
 */
- (BOOL)hasInterface:(const char *)interface withPath:(const char *)path;

/**
 * @param[out] msgArg containing a signature a(oas)
 *                    an array of object paths and an array of interfaces
 *                    found on that object path
 *
 * @return ER_OK if successful
 */
- (QStatus)getMsgArg:(AJNMessageArgument *)msgArg;

@end





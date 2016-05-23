/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
#import "listener/LSFSDKLightingDelegate.h"
#import "LSFSDKTrackingID.h"

@class LSFSDKTransitionEffect;
@class LSFSDKLightingItemErrorEvent;

/**
 * Provides an interface for developers to implement and receive all transition effect related events in the
 * Lighting system. Developers will be notified when transition effects are added, modified, initialized, and
 * deleted from the lighting controller. Transition effects are considered initialized when all pulse effect
 * data has been received from the lighting controller.
 *
 * **Note:** Once implemented, the delegate must be registered with the LSFSDKLightingDirector in order
 * to receive TransitionEffect callbacks. See [LSFSDKLightingDirector addTransitionEffectDelegate:] for
 * more information.
 */
@protocol LSFSDKTransitionEffectDelegate <LSFSDKLightingDelegate>

/**
 * Triggered when all data has been received from the lighting controller for a particular LSFSDKTransitionEffect.
 *
 * @warning This callback will fire only once for each LSFSDKTransitionEffect when all data has been received from
 * the lighting controller.
 *
 * @warning The tracking ID is only valid for transition effects created within your application.
 *
 * @param trackingID Reference to LSFSDKTrackingID
 * @param transitionEffect Reference to LSFSDKTransitionEffect
 */
-(void)onTransitionEffectInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andTransitionEffect: (LSFSDKTransitionEffect *)transitionEffect;

/**
 * Triggered every time new data is received from the lighting controller for a particular LSFSDKTransitionEffect.
 *
 * @param transitionEffect Reference to LSFSDKTransitionEffect
 */
-(void)onTransitionEffectChanged: (LSFSDKTransitionEffect *)transitionEffect;

/**
 * Triggered when a particular LSFSDKTransitionEffect has been deleted from the lighting controller.
 *
 * @warning This callback will fire only once for each LSFSDKTransitionEffect when it is deleted from
 * the lighting controller.
 *
 * @param transitionEffect Reference to LSFSDKTransitionEffect
 */
-(void)onTransitionEffectRemoved: (LSFSDKTransitionEffect *)transitionEffect;

/**
 * Triggered when an error occurs on a LSFSDKTransitionEffect operation.
 *
 * @param error Reference to LSFSDKLightingItemErrorEvent
 */
-(void)onTransitionEffectError: (LSFSDKLightingItemErrorEvent *)error;

@end

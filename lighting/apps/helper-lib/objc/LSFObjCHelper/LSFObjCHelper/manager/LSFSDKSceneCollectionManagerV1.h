/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFSDKSceneCollectionManager.h"
#import "LSFSDKSceneV1.h"
#import "LSFSDKSceneDelegate.h"

@interface LSFSDKSceneCollectionManagerV1 : LSFSDKSceneCollectionManager

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager;
-(void)addSceneDelegate: (id<LSFSDKSceneDelegate>)sceneDelegate;
-(void)removeSceneDelegate: (id<LSFSDKSceneDelegate>)sceneDelegate;
-(LSFSDKSceneV1 *)addSceneWithID: (NSString *)sceneID;
-(LSFSDKSceneV1 *)addSceneWithModel: (LSFSceneDataModel *)sceneModel;
-(LSFSDKSceneV1 *)addSceneWithID: (NSString *)sceneID scene: (LSFSDKSceneV1 *)scene;
-(LSFSDKSceneV1 *)getSceneWithID: (NSString *)sceneID;
-(NSArray *)getScenes;
-(NSArray *)getScenesWithFilter: (id<LSFSDKLightingItemFilter>)filter;
-(NSArray *)getScenesCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter;
-(NSArray *)removeAllScenes;
-(LSFSDKSceneV1 *)removeSceneWithID: (NSString *)sceneID;
-(LSFSceneDataModel *)getModelWithID: (NSString *)sceneID;

@end

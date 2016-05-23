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
 *
 ******************************************************************************/
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_allseen_lsf_TransitionEffectManager */

#ifndef _Included_org_allseen_lsf_TransitionEffectManager
#define _Included_org_allseen_lsf_TransitionEffectManager
#ifdef __cplusplus
extern "C" {
#endif
#undef org_allseen_lsf_TransitionEffectManager_MAX_TRANSITION_EFFECTS
#define org_allseen_lsf_TransitionEffectManager_MAX_TRANSITION_EFFECTS 100L
/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    getAllTransitionEffectIDs
 * Signature: ()Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getAllTransitionEffectIDs
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    getTransitionEffect
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getTransitionEffect
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    applyTransitionEffectOnLamps
 * Signature: (Ljava/lang/String;[Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_applyTransitionEffectOnLamps
  (JNIEnv *, jobject, jstring, jobjectArray);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    applyTransitionEffectOnLampGroups
 * Signature: (Ljava/lang/String;[Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_applyTransitionEffectOnLampGroups
  (JNIEnv *, jobject, jstring, jobjectArray);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    getTransitionEffectName
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getTransitionEffectName
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    setTransitionEffectName
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_setTransitionEffectName
  (JNIEnv *, jobject, jstring, jstring, jstring);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    createTransitionEffect
 * Signature: (Lorg/allseen/lsf/sdk/TrackingID;Lorg/allseen/lsf/TransitionEffect;Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_createTransitionEffect
  (JNIEnv *, jobject, jobject, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    updateTransitionEffect
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/TransitionEffect;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_updateTransitionEffect
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    deleteTransitionEffect
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_deleteTransitionEffect
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    getTransitionEffectDataSet
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_TransitionEffectManager_getTransitionEffectDataSet
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    createNativeObject
 * Signature: (Lorg/allseen/lsf/ControllerClient;Lorg/allseen/lsf/TransitionEffectManagerCallback;)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_TransitionEffectManager_createNativeObject
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_allseen_lsf_TransitionEffectManager
 * Method:    destroyNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_TransitionEffectManager_destroyNativeObject
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
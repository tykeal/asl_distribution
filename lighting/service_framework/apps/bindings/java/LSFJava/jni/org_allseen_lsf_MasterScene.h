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
 *
 ******************************************************************************/
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_allseen_lsf_MasterScene */

#ifndef _Included_org_allseen_lsf_MasterScene
#define _Included_org_allseen_lsf_MasterScene
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_allseen_lsf_MasterScene
 * Method:    setScenes
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_MasterScene_setScenes
  (JNIEnv *, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_MasterScene
 * Method:    getScenes
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_allseen_lsf_MasterScene_getScenes
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_MasterScene
 * Method:    isDependentOnScene
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ResponseCode;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_MasterScene_isDependentOnScene
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_MasterScene
 * Method:    toString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_MasterScene_toString
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_MasterScene
 * Method:    createNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_MasterScene_createNativeObject
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_MasterScene
 * Method:    destroyNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_MasterScene_destroyNativeObject
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif

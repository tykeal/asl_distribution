/******************************************************************************
 * Copyright (c), AllSeen Alliance. All rights reserved.
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
/* Header for class org_allseen_lsf_test_SceneManagerCallbackTest */

#ifndef _Included_org_allseen_lsf_test_SceneManagerCallbackTest
#define _Included_org_allseen_lsf_test_SceneManagerCallbackTest
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    getAllSceneIDsReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getAllSceneIDsReplyCB
  (JNIEnv *, jobject, jobject, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    getSceneNameReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getSceneNameReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring, jstring, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    setSceneNameReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_setSceneNameReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    createSceneReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_createSceneReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    updateSceneReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_updateSceneReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    deleteSceneReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_deleteSceneReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    scenesNameChangedCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesNameChangedCB
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    scenesCreatedCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesCreatedCB
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    scenesUpdatedCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesUpdatedCB
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    scenesAppliedCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesAppliedCB
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    scenesDeletedCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_scenesDeletedCB
  (JNIEnv *, jobject, jobject, jobjectArray);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    updateSceneWithSceneElementsReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_updateSceneWithSceneElementsReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    getSceneWithSceneElementsReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;Lorg/allseen/lsf/SceneWithSceneElements;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getSceneWithSceneElementsReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring, jobject);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    getSceneReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;Lorg/allseen/lsf/Scene;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_getSceneReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring, jobject);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    applySceneReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_applySceneReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    createSceneWithTrackingReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_createSceneWithTrackingReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring, jlong);

/*
 * Class:     org_allseen_lsf_test_SceneManagerCallbackTest
 * Method:    createSceneWithSceneElementsReplyCB
 * Signature: (Lorg/allseen/lsf/SceneManagerCallback;Lorg/allseen/lsf/ResponseCode;Ljava/lang/String;J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_allseen_lsf_test_SceneManagerCallbackTest_createSceneWithSceneElementsReplyCB
  (JNIEnv *, jobject, jobject, jobject, jstring, jlong);

#ifdef __cplusplus
}
#endif
#endif

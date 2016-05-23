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
/* Header for class org_alljoyn_bus_samples_chat_Chat */

#ifndef _Included_org_alljoyn_bus_samples_chat_Chat
#define _Included_org_alljoyn_bus_samples_chat_Chat
#ifdef __cplusplus
extern "C" {
#endif
#undef org_alljoyn_bus_samples_chat_Chat_DIALOG_CONNECT
#define org_alljoyn_bus_samples_chat_Chat_DIALOG_CONNECT 1L
#undef org_alljoyn_bus_samples_chat_Chat_DIALOG_ADVERTISE
#define org_alljoyn_bus_samples_chat_Chat_DIALOG_ADVERTISE 2L
#undef org_alljoyn_bus_samples_chat_Chat_DIALOG_JOIN_SESSION
#define org_alljoyn_bus_samples_chat_Chat_DIALOG_JOIN_SESSION 3L
/*
 * Class:     org_alljoyn_bus_samples_chat_Chat
 * Method:    jniOnCreate
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_alljoyn_bus_samples_chat_Chat_jniOnCreate
    (JNIEnv *, jobject, jstring);

/*
 * Class:     org_alljoyn_bus_samples_chat_Chat
 * Method:    jniOnDestroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_alljoyn_bus_samples_chat_Chat_jniOnDestroy
    (JNIEnv *, jobject);

/*
 * Class:     org_alljoyn_bus_samples_chat_Chat
 * Method:    sendChatMsg
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_alljoyn_bus_samples_chat_Chat_sendChatMsg
    (JNIEnv *, jobject, jstring);

/*
 * Class:     org_alljoyn_bus_samples_chat_Chat
 * Method:    advertise
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_alljoyn_bus_samples_chat_Chat_advertise
    (JNIEnv *, jobject, jstring);

/*
 * Class:     org_alljoyn_bus_samples_chat_Chat
 * Method:    joinSession
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_alljoyn_bus_samples_chat_Chat_joinSession
    (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif

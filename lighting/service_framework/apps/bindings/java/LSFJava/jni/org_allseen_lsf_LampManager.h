/*
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
 */
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_allseen_lsf_LampManager */

#ifndef _Included_org_allseen_lsf_LampManager
#define _Included_org_allseen_lsf_LampManager
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getAllLampIDs
 * Signature: ()Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getAllLampIDs
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampManufacturer
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampManufacturer
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampName
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampName
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    setLampName
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_setLampName
  (JNIEnv *, jobject, jstring, jstring, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampDetails
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampDetails
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampParameters
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampParameters
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampParametersEnergyUsageMilliwattsField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampParametersEnergyUsageMilliwattsField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampParametersLumensField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampParametersLumensField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampState
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampState
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampStateOnOffField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateOnOffField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampStateHueField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateHueField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampStateSaturationField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateSaturationField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampStateBrightnessField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateBrightnessField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampStateColorTempField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateColorTempField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    resetLampState
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampState
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    resetLampStateOnOffField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateOnOffField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    resetLampStateHueField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateHueField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    resetLampStateSaturationField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateSaturationField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    resetLampStateBrightnessField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateBrightnessField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    resetLampStateColorTempField
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateColorTempField
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampState
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/LampState;J)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampState
  (JNIEnv *, jobject, jstring, jobject, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    pulseLampWithState
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/LampState;Lorg/allseen/lsf/LampState;JJJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_pulseLampWithState
  (JNIEnv *, jobject, jstring, jobject, jobject, jlong, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    strobeLampWithState
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/LampState;Lorg/allseen/lsf/LampState;JJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_strobeLampWithState
  (JNIEnv *, jobject, jstring, jobject, jobject, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    cycleLampWithState
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/LampState;Lorg/allseen/lsf/LampState;JJJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_cycleLampWithState
  (JNIEnv *, jobject, jstring, jobject, jobject, jlong, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    pulseLampWithPreset
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JJJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_pulseLampWithPreset
  (JNIEnv *, jobject, jstring, jstring, jstring, jlong, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    strobeLampWithPreset
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_strobeLampWithPreset
  (JNIEnv *, jobject, jstring, jstring, jstring, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    cycleLampWithPreset
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JJJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_cycleLampWithPreset
  (JNIEnv *, jobject, jstring, jstring, jstring, jlong, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampStateOnOffField
 * Signature: (Ljava/lang/String;Z)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateOnOffField
  (JNIEnv *, jobject, jstring, jboolean);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampStateHueField
 * Signature: (Ljava/lang/String;JJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateHueField
  (JNIEnv *, jobject, jstring, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampStateSaturationField
 * Signature: (Ljava/lang/String;JJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateSaturationField
  (JNIEnv *, jobject, jstring, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampStateBrightnessField
 * Signature: (Ljava/lang/String;JJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateBrightnessField
  (JNIEnv *, jobject, jstring, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampStateColorTempField
 * Signature: (Ljava/lang/String;JJ)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateColorTempField
  (JNIEnv *, jobject, jstring, jlong, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    transitionLampStateToPreset
 * Signature: (Ljava/lang/String;Ljava/lang/String;J)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateToPreset
  (JNIEnv *, jobject, jstring, jstring, jlong);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampFaults
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampFaults
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampRemainingLife
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampRemainingLife
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampServiceVersion
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampServiceVersion
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    clearLampFault
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/LampFaultCode;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_clearLampFault
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    getLampSupportedLanguages
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_LampManager_getLampSupportedLanguages
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    createNativeObject
 * Signature: (Lorg/allseen/lsf/ControllerClient;Lorg/allseen/lsf/LampManagerCallback;)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampManager_createNativeObject
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_allseen_lsf_LampManager
 * Method:    destroyNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampManager_destroyNativeObject
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif

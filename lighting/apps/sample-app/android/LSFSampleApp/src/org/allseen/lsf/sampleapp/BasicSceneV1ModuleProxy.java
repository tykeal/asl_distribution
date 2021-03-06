/*
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
 */
package org.allseen.lsf.sampleapp;

import java.lang.reflect.Method;

import org.allseen.lsf.sdk.Scene;

import android.util.Log;

public class BasicSceneV1ModuleProxy {
    private final Object basicSceneV1Module;

    private final Method doDeleteSceneElementMethod;
    private final Method resetPendingSceneMethod;
    private final Method resetPendingEffectsMethod;
    private final Method createMemberNamesStringMethod;
    private final Method isNoEffectPendingMethod;
    private final Method isTransitionEffectPendingMethod;
    private final Method isPulseEffectPendingMethod;
    private final Method getPendingNoEffectIDMethod;
    private final Method getPendingTransitionEffectIDMethod;
    private final Method getPendingPulseEffectIDMethod;
    private final Method createBasicSceneInfoFragmentMethod;
    private final Method createSceneElementPresetsFragmentMethod;
    private final Method createBasicSceneEnterNameFragmentMethod;
    private final Method createBasicSceneSelectMembersFragmentMethod;
    private final Method createBasicSceneSelectEffectTypeFragmentMethod;
    private final Method createNoEffectFragmentMethod;
    private final Method createTransitionEffectFragmentMethod;
    private final Method createPulseEffectFragmentMethod;


    public BasicSceneV1ModuleProxy() {
        Class<?> basicSceneV1ModuleClass = classForName("org.allseen.lsf.sampleapp.scenesv1.BasicSceneV1Module");

        basicSceneV1Module = newInstance(basicSceneV1ModuleClass);

        doDeleteSceneElementMethod = getMethod(basicSceneV1ModuleClass, "doDeleteSceneElement", String.class);
        resetPendingSceneMethod = getMethod(basicSceneV1ModuleClass, "resetPendingScene", String.class);
        resetPendingEffectsMethod = getMethod(basicSceneV1ModuleClass, "resetPendingEffects");
        createMemberNamesStringMethod = getMethod(basicSceneV1ModuleClass, "createMemberNamesString", SampleAppActivity.class, Scene.class, String.class);
        isNoEffectPendingMethod = getMethod(basicSceneV1ModuleClass, "isNoEffectPending");
        isTransitionEffectPendingMethod = getMethod(basicSceneV1ModuleClass, "isTransitionEffectPending");
        isPulseEffectPendingMethod = getMethod(basicSceneV1ModuleClass, "isPulseEffectPending");
        getPendingNoEffectIDMethod = getMethod(basicSceneV1ModuleClass, "getPendingNoEffectID");
        getPendingTransitionEffectIDMethod = getMethod(basicSceneV1ModuleClass, "getPendingTransitionEffectID");
        getPendingPulseEffectIDMethod = getMethod(basicSceneV1ModuleClass, "getPendingPulseEffectID");

        createBasicSceneInfoFragmentMethod = getMethod(basicSceneV1ModuleClass, "createBasicSceneInfoFragment");
        createSceneElementPresetsFragmentMethod = getMethod(basicSceneV1ModuleClass, "createSceneElementPresetsFragment");
        createBasicSceneEnterNameFragmentMethod = getMethod(basicSceneV1ModuleClass, "createBasicSceneEnterNameFragment");
        createBasicSceneSelectMembersFragmentMethod = getMethod(basicSceneV1ModuleClass, "createBasicSceneSelectMembersFragment");
        createBasicSceneSelectEffectTypeFragmentMethod = getMethod(basicSceneV1ModuleClass, "createBasicSceneSelectEffectTypeFragment");
        createNoEffectFragmentMethod = getMethod(basicSceneV1ModuleClass, "createNoEffectFragment");
        createTransitionEffectFragmentMethod = getMethod(basicSceneV1ModuleClass, "createTransitionEffectFragment");
        createPulseEffectFragmentMethod = getMethod(basicSceneV1ModuleClass, "createPulseEffectFragment");
    }

    public boolean isModuleInstalled() {
        return basicSceneV1Module != null;
    }

    public void doDeleteSceneElement(String elementID) {
        invokeMethod(doDeleteSceneElementMethod, basicSceneV1Module, elementID);
    }

    public void resetPendingScene(String popupItemID) {
        invokeMethod(resetPendingSceneMethod, basicSceneV1Module, popupItemID);
    }

    public void resetPendingEffects() {
        invokeMethod(resetPendingEffectsMethod, basicSceneV1Module);
    }

    public String createMemberNamesString(SampleAppActivity activity, Scene basicScene, String separator) {
        return (String)invokeMethod(createMemberNamesStringMethod, basicSceneV1Module, activity, basicScene, separator);
    }

    public boolean isNoEffectPending() {
        return (Boolean)invokeMethod(isNoEffectPendingMethod, basicSceneV1Module);
    }

    public boolean isTransitionEffectPending() {
        return (Boolean)invokeMethod(isTransitionEffectPendingMethod, basicSceneV1Module);
    }

    public boolean isPulseEffectPending() {
        return (Boolean)invokeMethod(isPulseEffectPendingMethod, basicSceneV1Module);
    }

    public String getPendingNoEffectID() {
        return (String)invokeMethod(getPendingNoEffectIDMethod, basicSceneV1Module);
    }

    public String getPendingTransitionEffectID() {
        return (String)invokeMethod(getPendingTransitionEffectIDMethod, basicSceneV1Module);
    }

    public String getPendingPulseEffectID() {
        return (String)invokeMethod(getPendingPulseEffectIDMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createBasicSceneInfoFragment() {
        return (PageFrameChildFragment)invokeMethod(createBasicSceneInfoFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createSceneElementPresetsFragment() {
        return (PageFrameChildFragment)invokeMethod(createSceneElementPresetsFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createBasicSceneEnterNameFragment() {
        return (PageFrameChildFragment)invokeMethod(createBasicSceneEnterNameFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createBasicSceneSelectMembersFragment() {
        return (PageFrameChildFragment)invokeMethod(createBasicSceneSelectMembersFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createBasicSceneSelectEffectTypeFragment() {
        return (PageFrameChildFragment)invokeMethod(createBasicSceneSelectEffectTypeFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createNoEffectFragment() {
        return (PageFrameChildFragment)invokeMethod(createNoEffectFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createTransitionEffectFragment() {
        return (PageFrameChildFragment)invokeMethod(createTransitionEffectFragmentMethod, basicSceneV1Module);
    }

    public PageFrameChildFragment createPulseEffectFragment() {
        return (PageFrameChildFragment)invokeMethod(createPulseEffectFragmentMethod, basicSceneV1Module);
    }

    private Class<?> classForName(String className) {
        Class<?> clazz = null;

        try {
            // Use reflection for loose coupling with the optional Scene V1 feature
            clazz = Class.forName(className);
            Log.d(SampleAppActivity.TAG_TRACE, "found module " + className);
        } catch (Exception e) {
            Log.d(SampleAppActivity.TAG_TRACE, "missing module " + className);
        }

        return clazz;
    }

    private Object newInstance(Class<?> clazz) {
        Object instance = null;

        try {
            if (clazz != null) {
                instance = clazz.newInstance();
                logErrorIfNull(instance, "newInstance() failed");
            }
        } catch (Exception e) {
            logError("newInstance() failed: " + e.toString());
        }

        return instance;
    }

    private Method getMethod(Class<?> clazz, String name, Class<?>... parameterTypes) {
        Method method = null;

        try {
            if (clazz != null) {
                method = clazz.getMethod(name, parameterTypes);
                logErrorIfNull(method, "getMethod() failed for " + name);
            }
        } catch (Exception e) {
            logError("getMethod() failed: " + e.toString());
        }

        return method;
    }

    private Object invokeMethod(Method method, Object receiver, Object... args) {
        Object result = null;

        if (method != null && receiver != null) {
            try {
                result = method.invoke(receiver, args);
            } catch (Exception e) {
                logError("invoke() failed: " + e.toString());
            }
        }

        return result;
    }

    private void logErrorIfNull(Object object, String message) {
        if (object == null) {
            logError(message);
        }
    }

    private void logError(String message) {
        Log.e(SampleAppActivity.TAG, this.getClass().getSimpleName() + message);
    }
}

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
package org.allseen.lsf.sampleapp;

import org.allseen.lsf.LampGroup;

public class BasicSceneElementDataModel extends DimmableItemDataModel {
    public static final char TAG_PREFIX_SCENE_ELEMENT = 's';

    protected static int nextID = 1;

    public final EffectType type;
    public LampGroup members;
    public String presetID;

    public BasicSceneElementDataModel() {
        this(null, "");
    }

    public BasicSceneElementDataModel(EffectType type, String name) {
        super(String.valueOf(nextID++), TAG_PREFIX_SCENE_ELEMENT, name);

        this.type = type;
        this.members = new LampGroup();

        // State is always set to "on". To turn the lamp off as part of an effect,
        // you have to set the brightness to zero
        this.state.setOnOff(true);

        this.capability.dimmable = CapabilityData.ALL;
        this.capability.color = CapabilityData.ALL;
        this.capability.temp = CapabilityData.ALL;
    }

    public BasicSceneElementDataModel(BasicSceneElementDataModel other) {
        super(other);

        this.type = other.type;
        this.members = new LampGroup(other.members);
        this.presetID = other.presetID;
    }

    public boolean containsGroup(String groupID) {
        String[] childIDs = members.getLampGroups();

        for (String childID : childIDs) {
            if (childID.equals(groupID)) {
                return true;
            }
        }

        return false;
    }

    public boolean containsPreset(String presetID) {
        //TODO-FIX
        return false;
    }
}

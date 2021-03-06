/*******************************************************************************
*  Copyright (c) AllSeen Alliance. All rights reserved.
*
*     Contributed by Qualcomm Connected Experiences, Inc.,
*     with authorization from the AllSeen Alliance, Inc.
*     
*     Licensed under the Apache License, Version 2.0 (the "License");
*     you may not use this file except in compliance with the License.
*     You may obtain a copy of the License at
*     
*         http://www.apache.org/licenses/LICENSE-2.0
*     
*     Unless required by applicable law or agreed to in writing, software
*     distributed under the License is distributed on an "AS IS" BASIS,
*     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*     See the License for the specific language governing permissions and
*     limitations under the License.
*     
*     Pursuant to Section 1 of the License, the work of authorship constituting
*     a Work and any Contribution incorporated in the Work shall mean only that
*     Contributor's code submissions authored by that Contributor.  Any rights
*     granted under the License are conditioned upon acceptance of these
*     clarifications.
*******************************************************************************/
package org.alljoyn.validation.testing.suites.controller.alljoyn;

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Position;

@BusInterface(name = "org.allseen.LSF.ControllerService.PulseEffect")
public interface ControllerServicePulseEffectBusInterface
{
/*
    "   <property name="Version" type="u" access="read" />"
*/
    @BusProperty(signature="u")
    public int getVersion() throws BusException;

    public class PulseEffectValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String pulseEffectID;
    }

/* from service_framework\standard_core_library\lighting_controller_service\src\ServiceDescription.cc */

/*
    "    <method name='GetAllPulseEffectIDs'>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectIDs' type='as' direction='out'/>"
    "    </method>"
 */

    public class GetAllPulseEffectIDsValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String[] pulseEffectIDs;
    }

    @BusMethod(replySignature = "uas")
    public GetAllPulseEffectIDsValues GetAllPulseEffectIDs() throws BusException;

/*
    "    <method name='GetPulseEffectName'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='language' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "      <arg name='language' type='s' direction='out'/>"
    "      <arg name='pulseEffectName' type='s' direction='out'/>"
    "    </method>"
 */

    public class GetPulseEffectNameValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String pulseEffectID;
        @Position(2)
        public String language;
        @Position(3)
        public String pulseEffectName;
    }

    @BusMethod(signature = "ss", replySignature = "usss")
    public GetPulseEffectNameValues GetPulseEffectName(String pulseEffectID, String language) throws BusException;

/*
    "    <method name='SetPulseEffectName'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='pulseEffectName' type='s' direction='in'/>"
    "      <arg name='language' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "      <arg name='language' type='s' direction='out'/>"
    "    </method>"
 */

    public class SetPulseEffectNameValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String pulseEffectID;
        @Position(2)
        public String language;
    }

    @BusMethod(signature = "sss", replySignature = "uss")
    public SetPulseEffectNameValues SetPulseEffectName(String pulseEffectID, String pulseEffectName, String language) throws BusException;

/*
    "    <method name='CreatePulseEffect'>"
    "      <arg name='toLampState' type='a{sv}' direction='in'/>"
    "      <arg name='pulsePeriod' type='u' direction='in'/>"
    "      <arg name='pulseDuration' type='u' direction='in'/>"
    "      <arg name='numPulses' type='u' direction='in'/>"
    "      <arg name='fromLampState' type='a{sv}' direction='in'/>"
    "      <arg name='toPresetID' type='s' direction='in'/>"
    "      <arg name='fromPresetID' type='s' direction='in'/>"
    "      <arg name='pulseEffectName' type='s' direction='in'/>"
    "      <arg name='language' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "    </method>"
 */

    @BusMethod(signature = "a{sv}uuua{sv}ssss", replySignature = "us")
    public PulseEffectValues CreatePulseEffect(Map<String, Variant> toLampState, int pulsePeriod, int pulseDuration, int numPulses, Map<String, Variant> fromLampState, String toPresetID, String fromPresetID, String pulseEffectName, String language) throws BusException;

/*
    "    <method name='UpdatePulseEffect'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='toLampState' type='a{sv}' direction='in'/>"
    "      <arg name='pulsePeriod' type='u' direction='in'/>"
    "      <arg name='pulseDuration' type='u' direction='in'/>"
    "      <arg name='numPulses' type='u' direction='in'/>"
    "      <arg name='fromLampState' type='a{sv}' direction='in'/>"
    "      <arg name='toPresetID' type='s' direction='in'/>"
    "      <arg name='fromPresetID' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "    </method>"
 */

    @BusMethod(signature = "sa{sv}uuua{sv}ss", replySignature = "us")
    public PulseEffectValues UpdatePulseEffect(String pulseEffectID, Map<String, Variant> toLampState, int pulsePeriod, int pulseDuration, int numPulses, Map<String, Variant> fromLampState, String toPresetID, String fromPresetID) throws BusException;

/*
    "    <method name='DeletePulseEffect'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "    </method>"
 */

    @BusMethod(signature = "s", replySignature = "us")
    public PulseEffectValues DeletePulseEffect(String pulseEffectID) throws BusException;

/*
    "    <method name='GetPulseEffect'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "      <arg name='toLampState' type='a{sv}' direction='out'/>"
    "      <arg name='pulsePeriod' type='u' direction='out'/>"
    "      <arg name='pulseDuration' type='u' direction='out'/>"
    "      <arg name='numPulses' type='u' direction='out'/>"
    "      <arg name='fromLampState' type='a{sv}' direction='out'/>"
    "      <arg name='toPresetID' type='s' direction='out'/>"
    "      <arg name='fromPresetID' type='s' direction='out'/>"
    "    </method>"
 */

    public class GetPulseEffectValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String pulseEffectID;
        @Position(2)
        public Map<String, Variant> toLampState;
        @Position(3)
        public int pulsePeriod;
        @Position(4)
        public int pulseDuration;
        @Position(5)
        public int numPulses;
        @Position(6)
        public Map<String, Variant> fromLampState;
        @Position(7)
        public String toPresetID;
        @Position(8)
        public String fromPresetID;

    }

    @BusMethod(signature = "s", replySignature = "usa{sv}uuua{sv}ss")
    public GetPulseEffectValues GetPulseEffect(String pulseEffectID) throws BusException;

/*
    "    <method name='ApplyPulseEffectOnLamps'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='lampIDs' type='as' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "      <arg name='lampIDs' type='as' direction='out'/>"
    "    </method>"
 */

    public class ApplyPulseEffectOnLampsValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String pulseEffectID;
        @Position(2)
        public String[] lampIDs;
    }

    @BusMethod(signature = "sas", replySignature = "usas")
    public ApplyPulseEffectOnLampsValues ApplyPulseEffectOnLamps(String pulseEffectID, String[] lampIDs) throws BusException;

/*
    "    <method name='ApplyPulseEffectOnLampGroups'>"
    "      <arg name='pulseEffectID' type='s' direction='in'/>"
    "      <arg name='lampGroupIDs' type='as' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='pulseEffectID' type='s' direction='out'/>"
    "      <arg name='lampGroupIDs' type='as' direction='out'/>"
    "    </method>"
 */

    public class ApplyPulseEffectOnLampGroupsValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String pulseEffectID;
        @Position(2)
        public String[] lampGroupIDs;
    }

    @BusMethod(signature = "sas", replySignature = "usas")
    public ApplyPulseEffectOnLampGroupsValues ApplyPulseEffectOnLampGroups(String pulseEffectID, String[] lampGroupIDs) throws BusException;

/*
    "    <signal name='PulseEffectsNameChanged'>"
    "      <arg name='pulseEffectIDs' type='as' direction='out'/>"
    "    </signal>"
 */

    @BusSignal()
    public void PulseEffectsNameChanged(String[] pulseEffectIDs) throws BusException;
/*
    "    <signal name='PulseEffectsCreated'>"
    "      <arg name='pulseEffectsIDs' type='as' direction='out'/>"
    "    </signal>"
 */

    @BusSignal()
    public void PulseEffectsCreated(String[] pulseEffectIDs) throws BusException;
/*
    "    <signal name='PulseEffectsUpdated'>"
    "      <arg name='pulseEffectsIDs' type='as' direction='out'/>"
    "    </signal>"
 */

    @BusSignal()
    public void PulseEffectsUpdated(String[] pulseEffectIDs) throws BusException;

/*
    "    <signal name='PulseEffectsDeleted'>"
    "      <arg name='pulseEffectsIDs' type='as' direction='out'/>"
    "    </signal>"
 */

    @BusSignal()
    public void PulseEffectsDeleted(String[] pulseEffectIDs) throws BusException;

}

/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.onboarding.transport;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusAnnotation;
import org.alljoyn.bus.annotation.BusAnnotations;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.Secure;

/**
 * Definition of the Onboarding BusInterface
 */
@BusInterface(name = OnboardingTransport.INTERFACE_NAME)
@Secure
public interface OnboardingTransport extends BusObject {
    public static final String INTERFACE_NAME = "org.alljoyn.Onboarding";
    public final static String OBJ_PATH = "/Onboarding";

    /**
     * These enumeration values are used to indicate the ConfigureWifi possible modes
     */
    public static enum ConfigureWifiMode {

        /**
         * Wi-Fi standard mode
         */
        REGULAR((short) 1),

        /**
         * Wi-Fi fast channel mode
         */
        FAST_CHANNNEL((short) 2);

        private final short value;


        private ConfigureWifiMode(short value) {
            this.value = value;
        }


        public short getValue() {
            return value;
        }

        public static ConfigureWifiMode getConfigureWifiModeByValue(short value) {
            ConfigureWifiMode retState = null;
            for (ConfigureWifiMode responseType : ConfigureWifiMode.values()) {
                if (value == responseType.getValue()) {
                    retState = responseType;
                    break;
                }
            }
            return retState;
        }
    }

    /**
     * @return the interface version
     * @throws BusException
     */
    @BusProperty(signature = "q")
    public short getVersion() throws BusException;

    /**
     * @return the state:
     *       0 - Personal AP Not Configured
     *       1 - Personal AP Configured/Not Validated
     *       2 - Personal AP Configured/Validating
     *       3 - Personal AP Configured/Validated
     *       4 - Personal AP Configured/Error
     *       5 - Personal AP Configured/Retry
     * @throws BusException
     */
    @BusProperty(signature = "n")
    public short getState() throws BusException;

    /**
     * @return the last error 0 - Validated 1 - Unreachable 2 -
     *         Unsupported_protocol 3 - Unauthorized 4 - Error_message
     * @throws BusException
     */
    @BusProperty(signature = "(ns)")
    public OBLastError getLastError() throws BusException;

    /**
     * Tell the onboardee to connect to the Personal AP. The onboardee is
     * recommended to use channel switching feature if it is available.
     *
     * @throws BusException
     */
    @BusMethod()
    @BusAnnotations({ @BusAnnotation(name = "org.freedesktop.DBus.Method.NoReply", value = "true") })
    public void Connect() throws BusException;

    /**
     * Send the personal AP info to the onboardee. When the authType is equal to
     * "any", the onboardee needs to try out all the possible authentication
     * types it supports to connect to the AP. If authType parameter is invalid
     * then the AllJoyn error code org.alljoyn.Error.OutOfRange will be returned
     *
     * @param ssid
     * @param passphrase
     * @param WPA2_AUTO = -3,
     *        WPA_AUTO = -2,
     *        any = -1,
     *        Open = 0 ,
     *        WEP = 1,
     *        WPA_TKIP =2,
     *        WPA_CCMP = 3,
     *        WPA2_TKIP = 4,
     *        WPA2_CCMP = 5,
     *        WPS = 6
     * @throws BusException
     */
    @BusMethod(signature = "ssn", replySignature = "n")
    public short ConfigureWiFi(String ssid, String passphrase, short authType) throws BusException;

    /**
     * Tell the onboardee to disconnect from the personal AP, clear the personal
     * AP configuration fields, and start the soft AP mode.
     */
    @BusMethod()
    @BusAnnotations({ @BusAnnotation(name = "org.freedesktop.DBus.Method.NoReply", value = "true") })
    public void Offboard() throws BusException;

    /**
     * Scan all the WiFi access points in the onboardee's proximity. Some device
     * may not support this feature.
     *
     * @throws BusException
     *             if feature is unsupported, AllJoyn error code
     *             org.alljoyn.Error.FeatureNotAvailable will be returned in the
     *             AllJoyn response.
     */
    @BusMethod(replySignature = "qa(sn)")
    public ScanInfo GetScanInfo() throws BusException;

    /**
     * Signal received after ConfigureWiFi status is 2
     *
     * @param connectionResultAJ
     */
    @BusSignal(signature = "(ns)")
    public void ConnectionResult(ConnectionResultAJ connectionResultAJ);
}

/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
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
package org.alljoyn.validation.testing.it;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusAnnotation;
import org.alljoyn.bus.annotation.BusAnnotations;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.ns.transport.interfaces.NotificationDismisser;
import org.alljoyn.ns.transport.interfaces.NotificationProducer;
import org.alljoyn.onboarding.transport.OBLastError;
import org.alljoyn.onboarding.transport.ScanInfo;
import org.alljoyn.validation.testing.utils.audio.AudioTransports;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.AudioSinkDelay;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.Configuration;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.VolumeRange;

import android.util.Log;

public class RegisterInterfaces
{
    private static final String TAG = RegisterInterfaces.class.getSimpleName();
    private BusAttachment busAttachment;
    private Set<BusObject> busObjectSet = new HashSet<BusObject>();

    public RegisterInterfaces(BusAttachment busAttachment)
    {
        this.busAttachment = busAttachment;
    }

    public void registerOtherObjects()
    {
        BusObject busObject = new StreamBusObject();
        Status status = busAttachment.registerBusObject(busObject, "/introspection/Stream");
        checkStatus("registerBusObject Stream", status, true);
        busObjectSet.add(busObject);

        busObject = new PortBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/Port");
        checkStatus("registerBusObject Port", status, true);
        busObjectSet.add(busObject);

        busObject = new AudioSinkBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/AudioSink");
        checkStatus("registerBusObject AudioSink", status, true);
        busObjectSet.add(busObject);

        busObject = new AudioSourceBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/AudioSource");
        checkStatus("registerBusObject AudioSource", status, true);
        busObjectSet.add(busObject);

        busObject = new ImageSinkBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/ImageSink");
        checkStatus("registerBusObject ImageSink", status, true);
        busObjectSet.add(busObject);

        busObject = new ImageSourceBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/ImageSource");
        checkStatus("registerBusObject ImageSource", status, true);
        busObjectSet.add(busObject);

        busObject = new MetadataSinkBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/MetadataSink");
        checkStatus("registerBusObject MetadataSink", status, true);
        busObjectSet.add(busObject);

        busObject = new MetadataSourceBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/MetadataSource");
        checkStatus("registerBusObject MetadataSource", status, true);
        busObjectSet.add(busObject);

        busObject = new VolumeControlBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/VolumeControl");
        checkStatus("registerBusObject VolumeControl", status, true);
        busObjectSet.add(busObject);

        busObject = new ClockBusObject();
        status = busAttachment.registerBusObject(busObject, "/introspection/Clock");
        checkStatus("registerBusObject Clock", status, true);
        busObjectSet.add(busObject);

        busObject = new OnboardingSignalTransportBusObject();
        status = busAttachment.registerBusObject(busObject, "/Onboarding");
        checkStatus("registerBusObject Onboarding", status, true);
        busObjectSet.add(busObject);

        busObject = new NotificationProducerBusObject();
        status = busAttachment.registerBusObject(busObject, "/Notification");
        checkStatus("registerBusObject NotificationProducer", status, true);
        busObjectSet.add(busObject);

        busObject = new NotificationDismisserBusObject();
        status = busAttachment.registerBusObject(busObject, "/Notification");
        checkStatus("registerBusObject NotificationDismisser", status, true);
        busObjectSet.add(busObject);
    }

    private void checkStatus(String msg, Status status, boolean throwException)
    {
        if (!status.equals(Status.OK))
        {
            Log.e(TAG, msg + " returned status: " + status);
            if (throwException)
            {
                throw new RuntimeException(status.toString());
            }
        }
    }

    public void unregisterOtherObjects()
    {
        for (BusObject busObject : busObjectSet)
        {
            busAttachment.unregisterBusObject(busObject);
        }
        busObjectSet.clear();
    }

    public static class NotificationProducerBusObject implements NotificationProducer, BusObject
    {
        @Override
        @BusMethod(name = "Dismiss", signature = "i")
        public void dismiss(int arg0) throws BusException
        {
        }

        @Override
        @BusProperty(signature = "q")
        public short getVersion() throws BusException
        {
            return 0;
        }
    }

    public static class NotificationDismisserBusObject implements NotificationDismisser, BusObject
    {
        @Override
        @BusSignal(signature = "iay", name = "Dismiss")
        public void dismiss(int arg0, byte[] arg1) throws BusException
        {
        }

        @Override
        @BusProperty(signature = "q")
        public short getVersion() throws BusException
        {
            return 0;
        }
    }

    public static class StreamBusObject implements AudioTransports.Stream, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public void Open() throws BusException
        {
        }

        @Override
        public void Close() throws BusException
        {
        }

    }

    public static class PortBusObject implements AudioTransports.Port, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public byte getDirection() throws BusException
        {
            return 0;
        }

        @Override
        public Configuration[] getCapabilities() throws BusException
        {
            return null;
        }

        @Override
        public void OwnershipLost(String newOwner) throws BusException
        {
        }

        @Override
        public void Connect(String host, String objectPath, Configuration configuration)
        {
        }
    }

    public static class AudioSinkBusObject implements AudioTransports.AudioSink, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public int getFifoSize() throws BusException
        {
            return 0;
        }

        @Override
        public int getFifoPosition() throws BusException
        {
            return 0;
        }

        @Override
        public AudioSinkDelay getDelay() throws BusException
        {
            return null;
        }

        @Override
        public void FifoPositionChanged() throws BusException
        {
        }

        @Override
        public void PlayStateChanged(byte oldState, byte newState) throws BusException
        {
        }

        @Override
        public void Play() throws BusException
        {
        }

        @Override
        public void Pause(long timeNanos) throws BusException
        {
        }

        @Override
        public int Flush(long timeNanos) throws BusException
        {
            return 0;
        }
    }

    public static class AudioSourceBusObject implements AudioTransports.AudioSource, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public void Data(long timestamp, byte[] data) throws BusException
        {
        }
    }

    public static class ImageSinkBusObject implements AudioTransports.ImageSink, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }
    }

    public static class ImageSourceBusObject implements AudioTransports.ImageSource, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public void Data(byte[] data) throws BusException
        {
        }
    }

    public static class MetadataSinkBusObject implements AudioTransports.MetadataSink, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }
    }

    public static class MetadataSourceBusObject implements AudioTransports.MetadataSource, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public void Data(Map<String, Variant> dictionary) throws BusException
        {
        }
    }

    public static class VolumeControlBusObject implements AudioTransports.Volume, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 0;
        }

        @Override
        public boolean getMute() throws BusException
        {
            return false;
        }

        @Override
        public void setMute(boolean isMuted) throws BusException
        {

        }

        @Override
        public boolean getEnabled() throws BusException
        {
            return false;
        }

        @Override
        public void setEnabled(boolean enabled) throws BusException
        {

        }

        @Override
        public short getVolume() throws BusException
        {
            return 0;
        }

        @Override
        public void setVolume(short level) throws BusException
        {

        }

        @Override
        public VolumeRange getVolumeRange() throws BusException
        {
            return null;
        }

        @Override
        public void AdjustVolume(short delta) throws BusException
        {

        }

        @Override
        public void AdjustVolumePercent(double change) throws BusException
        {

        }

        @Override
        public void MuteChanged(boolean newMute) throws BusException
        {

        }

        @Override
        public void VolumeChanged(short newVolume) throws BusException
        {

        }

        @Override
        public void EnabledChanged(boolean newEnabled) throws BusException
        {

        }
    }

    public static class ClockBusObject implements AudioTransports.Clock, BusObject
    {
        @Override
        public short getVersion() throws BusException
        {
            return 1;
        }

        @Override
        public void SetTime(long timeNanos) throws BusException
        {
        }

        @Override
        public void AdjustTime(long timeNanos) throws BusException
        {
        }
    }

    @BusInterface(name = "org.alljoyn.Onboarding")
    @Secure
    public static class OnboardingSignalTransportBusObject implements BusObject
    {
        public static final java.lang.String INTERFACE_NAME = "org.alljoyn.Onboarding";
        public static final java.lang.String OBJ_PATH = "/Onboarding";

        @BusProperty(signature = "q")
        public short getVersion() throws BusException
        {
            return 0;
        }

        @BusProperty(signature = "n")
        public short getState() throws BusException
        {
            return 0;
        }

        @BusProperty(signature = "(ns)")
        public OBLastError getLastError() throws BusException
        {
            return null;
        }

        @BusMethod
        @BusAnnotations(value =
        { @BusAnnotation(name = "org.freedesktop.DBus.Method.NoReply", value = "true") })
        public void Connect() throws BusException
        {
        }

        @BusMethod(signature = "ssn", replySignature = "n")
        public short ConfigureWiFi(String arg0, String arg1, short arg2) throws BusException
        {
            return 0;
        }

        @BusMethod
        @BusAnnotations(value =
        { @BusAnnotation(name = "org.freedesktop.DBus.Method.NoReply", value = "true") })
        public void Offboard() throws BusException
        {
        }

        @BusMethod(replySignature = "qa(sn)")
        public ScanInfo GetScanInfo() throws BusException
        {
            return null;
        }

        @BusSignal(signature = "(ns)")
        public void ConnectionResult(OBLastError lastError) throws BusException
        {
        }
    }

}

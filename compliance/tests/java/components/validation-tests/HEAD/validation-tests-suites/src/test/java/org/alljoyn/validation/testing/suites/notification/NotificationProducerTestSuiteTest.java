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
package org.alljoyn.validation.testing.suites.notification;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import static org.mockito.Matchers.any;
import static org.mockito.Matchers.anyLong;
import static org.mockito.Matchers.anyString;
import static org.mockito.Matchers.eq;
import static org.mockito.Mockito.doAnswer;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.UUID;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;

import junit.framework.AssertionFailedError;

import org.alljoyn.about.client.AboutClient;
import org.alljoyn.bus.BusException;
import org.alljoyn.ns.NotificationSender;
import org.alljoyn.ns.NotificationService;
import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.framework.AppUnderTestDetails;
import org.alljoyn.validation.framework.UserInputDetails;
import org.alljoyn.validation.framework.UserResponse;
import org.alljoyn.validation.framework.ValidationTestContext;
import org.alljoyn.validation.framework.utils.introspection.BusIntrospector;
import org.alljoyn.validation.testing.suites.BaseTestSuiteTest;
import org.alljoyn.validation.testing.suites.MyRobolectricTestRunner;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.alljoyn.validation.testing.utils.notification.NotificationValidator;
import org.alljoyn.validation.testing.utils.notification.NotificationValidator.NotificationValidationExceptionHandler;
import org.alljoyn.validation.testing.utils.services.ServiceHelper;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.robolectric.annotation.Config;

@RunWith(MyRobolectricTestRunner.class)
@Config(manifest = Config.NONE)
public class NotificationProducerTestSuiteTest extends BaseTestSuiteTest
{

    private NotificationProducerTestSuite notificationProducerTestSuite;
    @Mock
    private ValidationTestContext mockTestContext;
    @Mock
    private NotificationService mockNotificationService;
    @Mock
    private NotificationSender mockNotificationSender;
    @Mock
    private AboutAnnouncementDetails mockAboutAnnouncement;
    @Mock
    private ServiceHelper mockServiceHelper;
    @Mock
    private ExecutorService mockExecutorService;
    @Mock
    private NotificationValidator mockNotificationValidator;
    @Mock
    private AboutClient mockAboutClient;
    @Mock
    private BusIntrospector mockBusIntrospector;

    private CountDownLatch waitForWaitForNextDeviceAnnouncementCall = new CountDownLatch(2);

    private String deviceId = "deviceId";
    private UUID appId = UUID.randomUUID();
    private AppUnderTestDetails appUnderTestDetails;

    @Before
    public void setup() throws Exception
    {
        MockitoAnnotations.initMocks(this);

        when(mockServiceHelper.waitForNextDeviceAnnouncement(anyLong(), any(TimeUnit.class))).thenAnswer(new Answer<AboutAnnouncement>()
        {

            @Override
            public AboutAnnouncement answer(InvocationOnMock invocation) throws Throwable
            {
                waitForWaitForNextDeviceAnnouncementCall.countDown();
                return mockAboutAnnouncement;
            }
        });

        when(mockAboutAnnouncement.getAppId()).thenReturn(appId);
        when(mockAboutAnnouncement.getDeviceId()).thenReturn(deviceId);

        notificationProducerTestSuite = new NotificationProducerTestSuite()
        {

            @Override
            protected ServiceHelper getServiceHelper()
            {
                return mockServiceHelper;
            }

            @Override
            protected ExecutorService getExecutorService()
            {
                return mockExecutorService;
            }

            @Override
            protected NotificationValidator getNotificationValidator()
            {
                return mockNotificationValidator;
            }
        };

        notificationProducerTestSuite.setValidationTestContext(mockTestContext);

        // provide the deviceId for the DUT to the test
        appUnderTestDetails = new AppUnderTestDetails(appId, deviceId);
        when(mockTestContext.getAppUnderTestDetails()).thenReturn(appUnderTestDetails);

        when(mockTestContext.waitForUserInput(any(UserInputDetails.class))).thenAnswer(new Answer<UserResponse>()
        {

            @Override
            public UserResponse answer(InvocationOnMock invocation) throws Throwable
            {
                return new UserResponse();

            }
        });

        when(mockServiceHelper.connectAboutClient(mockAboutAnnouncement)).thenReturn(mockAboutClient);
        when(mockServiceHelper.getBusIntrospector(mockAboutClient)).thenReturn(mockBusIntrospector);
        when(mockNotificationValidator.getNumberOfNotificationsReceived()).thenReturn(1);
    }

    @Test
    public void testBasicTextNotification() throws Exception
    {
        executeTestMethod(getTestWrapperFor_v1_01());

        verify(mockExecutorService).submit(mockNotificationValidator);
        verify(mockServiceHelper).initialize("NotificationProducerTestSuite", deviceId, appId);
        verify(mockServiceHelper).waitForNextDeviceAnnouncement(anyLong(), any(TimeUnit.class));
        verify(mockServiceHelper).release();

        verify(mockExecutorService).shutdownNow();
        verify(mockExecutorService).awaitTermination(anyLong(), any(TimeUnit.class));
        verify(mockAboutClient).disconnect();

    }

    @Test
    public void testExceptionFromInitialize() throws Exception
    {
        BusException be = new BusException();
        doThrow(be).when(mockServiceHelper).initialize(anyString(), anyString(), any(UUID.class));

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
            fail();
        }
        catch (BusException e)
        {
            assertEquals(be, e);
        }
        verify(mockServiceHelper).release();
    }

    @Test
    public void testTimedOutWaitingForAbout() throws Exception
    {
        when(mockServiceHelper.waitForNextDeviceAnnouncement(anyLong(), any(TimeUnit.class))).thenReturn(null);

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
            fail();
        }
        catch (Exception exception)
        {
            assertEquals("Timed out waiting for About announcement", exception.getMessage());
        }
        verify(mockServiceHelper).release();
    }

    @Test
    public void testExceptionFromConnectAboutClient() throws Exception
    {
        BusException be = new BusException("Failed to connect AboutClient to client: FAIL");
        doThrow(be).when(mockServiceHelper).connectAboutClient(mockAboutAnnouncement);

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
            fail();
        }
        catch (Exception e)
        {
            assertEquals(be, e);
        }
        verify(mockServiceHelper).release();
    }

    @Test
    public void testAwaitTerminationThrowsInterruptedException() throws Exception
    {
        doThrow(new InterruptedException()).when(mockExecutorService).awaitTermination(anyLong(), any(TimeUnit.class));

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
            fail();
        }
        catch (Exception e)
        {
            assertEquals("Interrupted while waiting for thread to exit", e.getMessage());
        }
        verify(mockServiceHelper).release();
    }

    @Test
    public void testNoNotifcations() throws Exception
    {
        when(mockNotificationValidator.getNumberOfNotificationsReceived()).thenReturn(0);

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
            fail();
        }
        catch (AssertionFailedError assertionFailedError)
        {
            assertEquals("No notifications received!", assertionFailedError.getMessage());
        }
        verify(mockServiceHelper).release();
    }

    @Test
    public void testWaitForUserInputThrowsInterruptedException() throws Exception
    {
        final Exception exception = new InterruptedException();

        when(mockTestContext.waitForUserInput(any(UserInputDetails.class))).thenThrow(exception);

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
            fail();
        }
        catch (Exception thrownException)
        {
            assertEquals(exception, thrownException);
        }

    }

    @Test
    public void testWaitForUserInputThrowsInterruptedExceptionAfterValidationException() throws Exception
    {
        final Exception exception = new Exception();

        doAnswer(new Answer<Object>()
        {

            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable
            {
                NotificationValidationExceptionHandler handler = (NotificationValidationExceptionHandler) invocation.getArguments()[2];
                handler.onNotificationValidationException(exception);
                return null;
            }
        }).when(mockNotificationValidator).initializeForDevice(eq(mockAboutAnnouncement), eq(mockBusIntrospector), any(NotificationValidationExceptionHandler.class));

        when(mockTestContext.waitForUserInput(any(UserInputDetails.class))).thenThrow(new InterruptedException());

        try
        {
            executeTestMethod(getTestWrapperFor_v1_01());
        }
        catch (Exception thrownException)
        {
            assertEquals(exception, thrownException);
        }

    }

    protected TestWrapper getTestWrapperFor_v1_01()
    {
        return new TestWrapper()
        {
            @Override
            public void executeTestMethod() throws Exception
            {
                notificationProducerTestSuite.testNotificationsReceived();
            }
        };
    }

    @Override
    protected void executeTestMethod(TestWrapper testWrapper) throws Exception
    {
        notificationProducerTestSuite.setUp();
        try
        {
            testWrapper.executeTestMethod();
        }
        finally
        {
            notificationProducerTestSuite.tearDown();
        }
    }

}

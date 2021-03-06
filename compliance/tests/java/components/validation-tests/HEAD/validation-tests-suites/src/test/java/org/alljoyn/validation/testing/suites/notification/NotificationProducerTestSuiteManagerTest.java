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

import static org.alljoyn.validation.framework.ValidationTestItem.DEFAULT_TEST_TIMEOUT_IN_MILLISECONDS;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;

import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.services.common.BusObjectDescription;
import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.framework.AllJoynAnnouncedDevice;
import org.alljoyn.validation.framework.ValidationTestGroup;
import org.alljoyn.validation.framework.ValidationTestItem;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

public class NotificationProducerTestSuiteManagerTest
{
    @Mock
    private AboutAnnouncementDetails mockAboutAnnouncement;
    @Mock
    private AboutAnnouncementDetails mockAboutAnnouncementWithoutNotification;

    private NotificationProducerTestSuiteManager notificationProducerTestSuiteManager;

    @Before
    public void setup()
    {
        MockitoAnnotations.initMocks(this);

        notificationProducerTestSuiteManager = new NotificationProducerTestSuiteManager();

        BusObjectDescription[] supportsNotification = new BusObjectDescription[1];

        BusObjectDescription bod = new BusObjectDescription();
        bod.interfaces = new String[]
        { "org.alljoyn.Notification" };
        bod.path = "/emergency";
        supportsNotification[0] = bod;

        when(mockAboutAnnouncement.getObjectDescriptions()).thenReturn(supportsNotification);
        when(mockAboutAnnouncement.getServiceName()).thenReturn("ServiceName1");

        BusObjectDescription[] supportsAbout = new BusObjectDescription[1];

        bod = new BusObjectDescription();
        bod.interfaces = new String[]
        { AboutTransport.INTERFACE_NAME };
        bod.path = "/About";
        supportsAbout[0] = bod;

        when(mockAboutAnnouncementWithoutNotification.getObjectDescriptions()).thenReturn(supportsAbout);
        when(mockAboutAnnouncementWithoutNotification.getServiceName()).thenReturn("ServiceName1");
    }

    @Test
    public void testSuiteWhenSupportingNotifications() throws Exception
    {
        AllJoynAnnouncedDevice mockAllJoynAnnouncedDevice = mock(AllJoynAnnouncedDevice.class);
        List<AboutAnnouncement> aboutAnnouncements = new ArrayList<AboutAnnouncement>();
        aboutAnnouncements.add(mockAboutAnnouncement);
        when(mockAllJoynAnnouncedDevice.getAnnouncements()).thenReturn(aboutAnnouncements);
        when(mockAboutAnnouncement.supportsInterface("org.alljoyn.Notification")).thenReturn(true);

        List<ValidationTestGroup> testGroups = notificationProducerTestSuiteManager.getApplicableTests(mockAllJoynAnnouncedDevice);

        assertEquals(1, testGroups.size());
        ValidationTestGroup testGroup = testGroups.get(0);

        validateValidationTestGroup(testGroup, mockAboutAnnouncement);
    }

    @Test
    public void testSuiteWhenNOtSupportingNotifications() throws Exception
    {
        AllJoynAnnouncedDevice mockAllJoynAnnouncedDevice = mock(AllJoynAnnouncedDevice.class);
        List<AboutAnnouncement> aboutAnnouncements = new ArrayList<AboutAnnouncement>();
        aboutAnnouncements.add(mockAboutAnnouncementWithoutNotification);
        when(mockAllJoynAnnouncedDevice.getAnnouncements()).thenReturn(aboutAnnouncements);

        List<ValidationTestGroup> testGroups = notificationProducerTestSuiteManager.getApplicableTests(mockAllJoynAnnouncedDevice);

        assertEquals(0, testGroups.size());
    }

    private void validateValidationTestGroup(ValidationTestGroup validationTestGroup, AboutAnnouncementDetails aboutAnnouncement)
    {
        assertEquals("Notification-v1", validationTestGroup.getTestGroupId());
        assertEquals(aboutAnnouncement.getServiceName(), validationTestGroup.getAboutAnnouncement().getServiceName());
        assertNull(validationTestGroup.getInterfaceName());
        assertNull(validationTestGroup.getObjectPath());

        validateValidationTestItems(validationTestGroup);
    }

    private void validateValidationTestItems(ValidationTestGroup validationTestGroup)
    {
        List<ValidationTestItem> validationTestItems = validationTestGroup.getTestItems();
        assertEquals(1, validationTestItems.size());

        validateValidationTestItem(validationTestItems.get(0), validationTestGroup, "Notification-v1-01");
    }

    private void validateValidationTestItem(ValidationTestItem validationTestItem, ValidationTestGroup validationTestGroup, String testCaseId)
    {
        assertEquals(validationTestGroup, validationTestItem.getTestGroup());
        assertEquals(testCaseId, validationTestItem.getTestCaseId());
        assertEquals(NotificationProducerTestSuite.class.getName(), validationTestItem.getClassName());
        assertEquals(DEFAULT_TEST_TIMEOUT_IN_MILLISECONDS, validationTestItem.getTimeoutInMilliseconds());
        assertTrue(validationTestItem.isInitiallySelected());
    }

}

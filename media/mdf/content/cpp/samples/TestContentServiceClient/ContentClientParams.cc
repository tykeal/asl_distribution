/******************************************************************************
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
 ******************************************************************************/

#include "ContentClientParams.h"
#include <ContentConstants.h>
#include <LogModule.h>
#include <alljoyn/Status.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <iostream>


namespace mdf {

ContentClientParams::ContentClientParams() : m_Bus(NULL),
    m_sessionOpts(NULL) {
}

ContentClientParams::~ContentClientParams() {
    delete m_Bus;
    delete m_sessionOpts;

}

BusAttachment* ContentClientParams::GetBusAttachment() {
    return m_Bus;
}

const SessionOpts* ContentClientParams::GetSessionOpts() {
    return m_sessionOpts;
}

QStatus ContentClientParams::Init() {
    QStatus status = ER_OK;
    if (m_Bus == NULL) {
        status = CreateBusAttachment();
        if (status != ER_OK) {
            QCC_LogError(ER_INIT_FAILED, ("Create Bus attachment failed"));
        }
    }

    if (status == ER_OK) {
        if (m_sessionOpts == NULL) {
            status = CreateSessionOpts();
            if (status != ER_OK) {
                QCC_LogError(ER_INIT_FAILED, ("Create Session Opts failed"));
            }
        }
    }

    //now we create the interface
    if (status == ER_OK) {
        status = m_Bus->CreateInterfacesFromXml(s_CONTENT_SOURCE_IF_XML.c_str());
        if (status == ER_OK) {
            //now check that all is in order with the xml
            const InterfaceDescription* contentSourceInterface = m_Bus->GetInterface(s_CONTENT_SOURCE_INTERFACE.c_str());
            if (contentSourceInterface != NULL) {
                if (contentSourceInterface->GetMember(s_METHOD_BROWSE.c_str()) == NULL) {
                    status = ER_INIT_FAILED;
                    QCC_LogError(status, ("Retrieving Browse method xml returned NULL"));
                }
                if (contentSourceInterface->GetMember(s_METHOD_GETITEM.c_str()) == NULL) {
                    status = ER_INIT_FAILED;
                    QCC_LogError(status, ("Retrieving GetItem method xml returned NULL"));
                }
                if (contentSourceInterface->GetMember(s_METHOD_GETID.c_str()) == NULL) {
                    status = ER_INIT_FAILED;
                    QCC_LogError(status, ("Retrieving GetID method xml returned NULL"));
                }
                if (contentSourceInterface->GetMember(s_METHOD_GETNAME.c_str()) == NULL) {
                    status = ER_INIT_FAILED;
                    QCC_LogError(status, ("Retrieving GetName method xml returned NULL"));
                }
                if (contentSourceInterface->GetMember(s_METHOD_GETDISPLAYNAME.c_str()) == NULL) {
                    status = ER_INIT_FAILED;
                    QCC_LogError(status, ("Retrieving GetDisplayName method xml returned NULL"));
                }
            } else {
                status = ER_INIT_FAILED;
                QCC_LogError(status, ("Retrieving the xml interface from the bus returned NULL"));
            }

        } else {
            QCC_LogError(status, ("Failed to create interfaces from XML!"));
        }
    }

    return status;
}

QStatus ContentClientParams::CreateBusAttachment()
{
    QStatus retVal = ER_OK;
    m_Bus = new BusAttachment("CommonServiceApp", true);
    if (m_Bus != NULL) {

        /* Start the BusAttachment */
        QStatus status = m_Bus->Start();
        if (status != ER_OK) {
            delete m_Bus;
            m_Bus = NULL;
            QCC_LogError(ER_INIT_FAILED, ("could not start the bus attachment"));
            retVal = ER_INIT_FAILED;
        }

        /* Connect to the daemon using address provided*/
        status = m_Bus->Connect();
        if (status != ER_OK) {
            delete m_Bus;
            m_Bus = NULL;
            QCC_LogError(ER_INIT_FAILED, ("could not connect to the bus attachment"));
            retVal = ER_INIT_FAILED;
        }
    } else {
        QCC_LogError(ER_INIT_FAILED, ("could not initialise the bus attachment"));
        retVal = ER_INIT_FAILED;
    }

    return retVal;
}

QStatus ContentClientParams::CreateSessionOpts() {
    QStatus retVal = ER_OK;

    m_sessionOpts = new SessionOpts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    if (m_sessionOpts == NULL) {
        QCC_LogError(ER_INIT_FAILED, ("could not initialise the session opts"));
        retVal = ER_INIT_FAILED;
    }
    return retVal;
}


} /* namespace mdf */

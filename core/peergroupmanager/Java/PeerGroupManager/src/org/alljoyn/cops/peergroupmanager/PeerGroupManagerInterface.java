/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.cops.peergroupmanager;

import java.util.ArrayList;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;

interface PeerGroupManagerInterface {
    
    public Status createGroup (String groupName);
    
    public Status createGroup (String groupName, boolean locked); 
    
    public Status destroyGroup (String groupName);
    
    public Status joinGroup (String groupName);
    
    public Status leaveGroup (String groupName);
    
    public JoinOrCreateReturn joinOrCreateGroup(String groupName); 
    
    public void cleanup();
    
    public Status unlockGroup(String groupName);
    
    public Status lockGroup(String groupName);
    
    public ArrayList<String> listFoundGroups();
    
    public ArrayList<String> listHostedGroups();
    
    public ArrayList<String> listJoinedGroups();
    
    public ArrayList<String> listLockedGroups();
    
    public ArrayList<String> getPeers (String groupName);
    
    public int getNumPeers(String groupName);
    
    public void addPeerGroupListener(PeerGroupListenerInterface peerGroupListener);

    public <T> T getRemoteObjectInterface(String peerId, String groupName, String objectPath, Class<T> iface);
    
    public <T> T getSignalInterface(String groupName, BusObject busObject, Class<T> iface);
    
    public <T> T getSignalInterface(String peerId, String groupName, BusObject busObject, Class<T> iface);
    
    public Status registerModule(PGModule module, String groupName);
    
    public String getGroupPrefix();
    
    public Status registerSignalHandlers(Object classWithSignalHandlers);
    
    public String getMyPeerId();
    
    public String getGUID();
    
    public String getSenderPeerId();
    
    public String getGroupHostPeerId(String groupName);
    
    public void setSessionPort(short sessionPort);
}

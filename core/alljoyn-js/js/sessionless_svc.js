/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
var AJ = require('AllJoyn');

AJ.interfaceDefinition["org.alljoyn.sessionless"] =
{
    my_signal:{ type:AJ.SIGNAL, args:[{inStr:"s"}], returns:[{outStr:"s"}] }
};

AJ.objectDefinition['/org/alljoyn/sessionless'] = {
    interfaces:['org.alljoyn.sessionless']
};

AJ.onAttach = function()
{
    AJ.addMatch('org.alljoyn.sessionless', 'my_signal')
    print('Attached');
}

AJ.onSignal = function() {
    if (this.member == 'my_signal') {
        print('SLS signal received');
    }
}

print('SLS service test program initialized\n');

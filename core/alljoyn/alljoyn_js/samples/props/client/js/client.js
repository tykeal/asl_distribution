/*
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
 */
var onDeviceReady = function() {
    var $ = function(id) {
        return document.getElementById(id);
    };

    var stringProp = $('stringProp'),
        intProp = $('intProp');

    stringProp.onkeypress = function(event) {
        var c = event.which ? event.which : event.keyCode;

        if (c === 13) {
            alljoyn.setStringProp(stringProp.value);
            return false;
        }
    };
    intProp.onkeypress = function(event) {
        var c = event.which ? event.which : event.keyCode;

        if (c === 13) {
            alljoyn.setIntProp(intProp.value);
            return false;
        }
    };

    alljoyn.onstringprop = function(value) {
        stringProp.placeholder = value;
    };
    alljoyn.onintprop = function(value) {
        intProp.placeholder = value;
    };
    alljoyn.start();
};

if (window.cordova) {
    document.addEventListener('deviceready', onDeviceReady, false);
} else {
    onDeviceReady();
}

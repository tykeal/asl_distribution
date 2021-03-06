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

package org.alljoyn.ioe.controlpanelservice.ui;

/**
 * Optional parameters keys of {@link PropertyWidget}
 */
public enum PropertyWidgetEnum {
	LABEL((short)0),
	BG_COLOR((short)1),
	HINTS((short)2),
	UNIT_OF_MEASURE((short)3),
	CONSTRAINT_TO_VALUES((short)4),
	RANGE((short)5)
	;
	
	/**
	 * The key number
	 */
	public final short ID;
	
	/**
	 * Constructor
	 * @param id
	 */
	private PropertyWidgetEnum(short id) {
		ID = id;
	}
}

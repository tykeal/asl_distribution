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
package org.alljoyn.aroundme.Groups;


import org.alljoyn.aroundme.R;
import org.alljoyn.aroundme.Adapters.GalleryContactAdapter;
import org.alljoyn.aroundme.MainApp.AppConstants;
import org.alljoyn.devmodules.common.ProfileDescriptor;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;

import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.TextView;



/*
 * Activity to display the options available for a group
 */
public class GroupFunctionsActivity extends Activity {

	private Menu                 mMenu;

	private static final String TAG = "GroupFunctionsActivity";

	// UI display variables for header
	private static TextView   nameView;
	private static TextView   numberView;
	private static ImageView  photoIcon;
	private static Button[]   buttonList;

	private static ProfileDescriptor mProfile ;
	private static GalleryContactAdapter mAdapter ;
	private static String   mName="";
	private static String   mService="";
	private static Intent mIntent;
	private static String mGroup = "";



	@Override
	public void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);

		setContentView(R.layout.groupfunctions);


		// get the Group Name
		mIntent = getIntent();
		mGroup = mIntent.getStringExtra(AppConstants.INTENT_PREFIX+".group"); 

		if ((mGroup==null) || (mGroup.length()<=0)){
			Log.e(TAG, "No group specified, exiting...");
			finish();
		} else {
			// Set group title
			TextView vGroup = (TextView)  findViewById(R.id.group);
			vGroup.setText(mGroup);
					
			// set up the function buttons
			setupButtons();
			
			//TODO: populate gallery with group members
		}
	} // onCreate


	@Override
	protected void onDestroy() {
		super.onDestroy();
		finish();
	} //onDestroy




	///////////////////////////////////////////////////////////////
	// Handling for the different buttons
	///////////////////////////////////////////////////////////////


	private class buttonDescriptor {
		buttonDescriptor (int r, String t, String i){
			resource = r;
			text     = t;
			intent   = i;
		}
		public int    resource;
		public String text;
		public String intent;
	}


	private buttonDescriptor[] buttonConfig = {
			new buttonDescriptor(R.id.btn01, "Settings",   "ADDGROUP"),
			new buttonDescriptor(R.id.btn02, "Chat",       "CHAT"),
			new buttonDescriptor(R.id.btn03, "Messages",   "MESSAGES"),
			new buttonDescriptor(R.id.btn04, "File Synch", "FILESYNCH"),
			new buttonDescriptor(R.id.btn05, "Whiteboard", "WHITEBOARD"),
			new buttonDescriptor(R.id.btn06, "Test",       "GROUPTEST"),
			new buttonDescriptor(R.id.btn07, "", ""),
			new buttonDescriptor(R.id.btn08, "", ""),
			new buttonDescriptor(R.id.btn09, "", "")
	};

	// routine to launch an activity


	// Setup the appearance and actions for the buttons
	private void setupButtons(){

		buttonList = new Button[buttonConfig.length];

		for (int i=0; i<buttonConfig.length; i++){
			buttonList[i] = (Button)  findViewById(buttonConfig[i].resource);
			buttonList[i].setText(buttonConfig[i].text);
			if (buttonConfig[i].text.length()==0)
				buttonList[i].setVisibility(View.INVISIBLE);
		}

		// can't dynamically create index-based handlers in a loop, so just declare each one
		buttonList[0].setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				launchGroupActivity (buttonConfig[0].intent);
			}	
		});

		buttonList[1].setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				launchGroupActivity (buttonConfig[1].intent);
			}	
		});

		buttonList[5].setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				launchGroupActivity (buttonConfig[5].intent);
			}	
		});
	}//setupButtons


	void launchGroupActivity(String activity) {
		// Launch a Service-specific Activity, setting the service name as a parameter
		Intent intent = new Intent();
		intent.setAction(AppConstants.INTENT_PREFIX + "." + activity);
		intent.putExtra(AppConstants.INTENT_PREFIX + ".group", mGroup);
		try {
			startActivity(intent);
		} catch (Exception e){
			Toast.makeText(this, 
					"Error starting " + activity + " Activity for group: " + mGroup, 
					Toast.LENGTH_SHORT).show();
			Log.e(TAG, "Launch error: "+e.toString());
		}

	}

} // GroupFunctionsActivity

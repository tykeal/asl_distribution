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
package org.alljoyn.aroundme.Adapters;


import org.alljoyn.aroundme.R;

import org.alljoyn.devmodules.common.ProfileDescriptor;
import org.alljoyn.devmodules.common.Utilities;

import java.util.ArrayList;
import java.util.HashMap;


import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.LayoutInflater;

import android.view.View;
import android.view.ViewGroup;

import android.widget.BaseAdapter;

import android.widget.ImageView;

import android.widget.TextView;


// List Management for profile data




//Adapter to deal with formatted strings
public class GridContactAdapter extends BaseAdapter { 


	private static final String TAG = "GridContactAdapter";

	// Arrays for holding the data
	// I keep a separate list of names so that they can be looked up by position rather than key
	private static HashMap<String,ProfileDescriptor> mContactList = new HashMap<String,ProfileDescriptor>();
	private static ArrayList<String> mNameList = new ArrayList<String>(); 

	// Context of the current View
	private static Context mContext; 


	private static GridContactAdapter _adapter; // the singleton version

	private static boolean viewAttached = false;


	private GridContactAdapter() { 
		// no implementation, just private to control usage

	} 


	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	// method to return reference to internal data
	public static synchronized GridContactAdapter getAdapter() {
		if (_adapter == null) {
			_adapter = new GridContactAdapter();
		}
		return _adapter;
	}

	public static synchronized void setContext (Context context){
		mContext = context;
		viewAttached = true;
	}

	public GridContactAdapter(Context c) { 
		mContext = c; 
		viewAttached = true;
	} 


	public int getCount() { 
		return mNameList.size(); 
	} 

	public Object getItem(int position) { 
		return position; 
	} 

	public long getItemId(int position) { 
		return position; 
	} 

	// utility for stripping the name to be just the unique id
	// allows for use of full/partial service name or directory-style names
	private static String extractId(String name){
		String id = name;
		if (id.contains(".")){ id = id.substring(id.lastIndexOf(".")+1); }
		if (id.contains("/")){ id = id.substring(id.lastIndexOf("/")+1); }
		return id;
	}
	
	
	public static synchronized String getProfileId(int position){
		String n = mNameList.get(position);
		//return Utilities.checkString (mContactList.get(n).getField(ProfileDescriptor.ProfileFields._ID));
		return n;
	}

	public static synchronized String getName(int position){
		String n = mNameList.get(position);
		return Utilities.checkString (mContactList.get(n).getField(ProfileDescriptor.ProfileFields.NAME_DISPLAY));
	}

	public static synchronized String getNumber(int position){
		String n = mNameList.get(position);
		return Utilities.checkString (mContactList.get(n).getField(ProfileDescriptor.ProfileFields.PHONE_HOME));
	}


	public static synchronized byte[] getPhoto(int position){
		String n = mNameList.get(position);
		return getPhoto(n);	
	}

	public static synchronized byte[] getPhoto(String name){
		byte[] photo ;

		if (name != null){
			String id = extractId(name);

			try {
				photo = mContactList.get(id).getPhoto();
			} catch (Exception e){
				Log.e(TAG, "getPhoto(): Error decoding photo ("+id+")"+e.toString());
				photo = new byte[0] ; 
			}
		} else {
			Log.e(TAG, "getPhoto(): No name supplied");
			photo = new byte[0] ; 
		}
		return photo;
	}



	public static synchronized boolean contains (String name){
		return (mNameList.contains(name)) ? true : false ;
	}

	
	public static synchronized ProfileDescriptor getProfile (int position){
		String n = mNameList.get(position);
		return mContactList.get(n);	
	}


	public static synchronized ProfileDescriptor getProfile (String name){
		ProfileDescriptor profile = new ProfileDescriptor();
		if (name != null){
			String id = extractId(name);

			if (mNameList.contains(id)){
				profile = mContactList.get(id);	
			} else {
				Log.w(TAG, "getProfile("+id+"): Profile entry not found");
				profile.setField(ProfileDescriptor.ProfileFields.NAME_DISPLAY, "(unknown)");
			}
		}
		return profile;
	}

	// Add an entry using the supplied name
	public static synchronized void add (String name, ProfileDescriptor profile) {
		if (profile!=null){
			String id = extractId(name);
			if (!mNameList.contains(id)){
				Utilities.logMessage(TAG, "Adding profile: "+id);
				profile.setField("profileid", id);
				profile.setField(ProfileDescriptor.ProfileFields._ID, id);
				mContactList.put(id, profile);
				mNameList.add(id);
				update();
			}
		} else {
			Log.e(TAG, "NULL ProfileDescriptor supplied");
		}
	}

	// add an entry, extracting the name from the profile
	public static synchronized void add (ProfileDescriptor profile) {
		if (profile!=null){
			String id = profile.getField("profileid");
			if ((id!=null) && (id.length()>0)){
				id = extractId(id);
				if (!mNameList.contains(id)){
					Utilities.logMessage(TAG, "Adding profile: "+id);
					mContactList.put(id, profile);
					mNameList.add(id);
					update();
				}
			} else {
				Log.e(TAG, "profileid field not set");
			}
		} else {
			Log.e(TAG, "NULL ProfileDescriptor supplied");
		}
	}

	public static synchronized void remove (String name) {
		String id = extractId(name);
		if (mContactList.containsKey(id)){
			mContactList.remove(id);
			mNameList.remove(id);
			update();
		} else {
			Log.e(TAG, "Entry not found: "+id);
		}
	}

	public static synchronized void clear(){
		mContactList.clear();
		mNameList.clear();
		update();
	}


	// return the View to be displayed
	public View getView(int position, View convertView, ViewGroup parent) { 

		TextView tv ;


		// Inflate a view template
		if (convertView == null) {
			LayoutInflater inflater = (LayoutInflater)mContext.getSystemService (Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.griditemsmall, parent, false);
		}

		// get the display views
		//TextView nameView = (TextView) convertView.findViewById(R.id.grid_item_text);
		ImageView photoIcon = (ImageView) convertView.findViewById(R.id.grid_item_image);

		// Populate name
		//String name = getName(position);
		//nameView.setText(name);

		// display icon, if specified
		try {

			// get the photo based on the supplied name
			// Note that it is possible to get a  message from a device that does not have
			// a profile registered , or no photo supplied, so we need the code to check for 
			// null and zero-length photos

			byte[] photo = getPhoto(position);
			if ((photo!=null) && photo.length>0){
				Bitmap image = BitmapFactory.decodeByteArray(photo, 0, photo.length);
				photoIcon.setImageBitmap(image);
			} else {
				photoIcon.setImageDrawable(mContext.getResources().getDrawable(R.drawable.ic_list_person));		
			}

		} catch (Exception e){
			// error somewhere, just set to default icon
			photoIcon.setImageDrawable(mContext.getResources().getDrawable(R.drawable.ic_list_person));		
		}

		// set the background attribute of the selection
		//convertView.setBackgroundResource(mGalleryItemBackground);
		//convertView.setBackgroundResource(R.drawable.gallerycurrentitem_selector);

		return convertView;

	} 

	private static void update() {
		if (_adapter == null) {
			_adapter = new GridContactAdapter();
		}
		_adapter.notifyDataSetChanged(); // force re-display of list
	}

} // GridContactAdapter

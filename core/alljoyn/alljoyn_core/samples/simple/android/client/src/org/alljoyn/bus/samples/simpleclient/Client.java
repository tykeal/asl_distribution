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

package org.alljoyn.bus.samples.simpleclient;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;


public class Client extends Activity {

    private static final int BUSNAMEITEM_FOUND = 1;
    private static final int BUSNAMEITEM_LOST = 2;
    private static final int BUSNAMEITEM_DISCONNECT = 3;

    private EditText editText;
    private BusNameItemAdapter busNameItemAdapter;
    private ListView listView;

    private Menu menu;

    /** Handler used to post messages from C++ into UI thread */
    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            BusNameItem item = (BusNameItem)msg.obj;
            Log.e("SimpleClient", String.format("handleMessage(arg1=%d, busName=%s", msg.arg1, item.getBusName()));
            switch (msg.arg1) {
            case BUSNAMEITEM_FOUND:
                busNameItemAdapter.add(item);
                break;
            case BUSNAMEITEM_LOST:
                busNameItemAdapter.remove(item);
                break;
            case BUSNAMEITEM_DISCONNECT:
            {
                final Button connectButton = (Button) findViewById(R.id.Connect);
                item.setSessionId(0);
                connectButton.setText("Connect");
                break;
            }

            default:
                break;
            }


            listView.invalidate();
        }
    };

    HandlerThread bus_thread = new HandlerThread("BusHandler");
    { bus_thread.start(); }
    Handler bus_handler = new Handler(bus_thread.getLooper());

    public Handler getBusHandler() {
        return bus_handler;
    }

    public Handler getUIHandler() {
        return handler;
    }

    /** Called when activity's onCreate is called */
    private native int simpleOnCreate(String packageName);

    /** Called when activity's onDestroy is called */
    private native void simpleOnDestroy();

    /** Called when user chooses to ping a remote SimpleSerivce. Must be connected to name */
    private native String simplePing(int sessionId, String name, String pingStr);

    /** Called when user selects "Connect" */
    public native int joinSession(String busName);

    /** Called when user selects "Disconnect" */
    public native boolean leaveSession(int sessionId);

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        busNameItemAdapter = new BusNameItemAdapter(this.getApplicationContext(), this);
        listView = (ListView) findViewById(R.id.ListView);
        listView.setAdapter(busNameItemAdapter);

        editText = (EditText) findViewById(R.id.EditText);

        listView.requestFocus();


        // Initialize the native part of the sample and connect to remote alljoyn instance
        bus_handler.post(new Runnable() {
            public void run() {
                final int ret = simpleOnCreate(getPackageName());
                if (0 != ret) {
                    handler.post(new Runnable() {
                        public void run() {
                            Toast.makeText(Client.this, "simpleOnCreate failed with " + ret, Toast.LENGTH_LONG).show();
                            finish();
                        }
                    });
                }
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        // Don't let this app run once it is off screen (it is confusing for a demo)
        this.finish();
    }

    @Override
    protected void onDestroy() {
        simpleOnDestroy();
        bus_handler.getLooper().quit();
        super.onDestroy();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.mainmenu, menu);
        this.menu = menu;
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle item selection
        switch (item.getItemId()) {
        case R.id.quit:
            finish();
            return true;

        default:
            return super.onOptionsItemSelected(item);
        }
    }

    public void closeKeyboard() {
        editText.clearFocus();
    }

    public void ping(final int sessionId, final String name) {
        bus_handler.post(new Runnable() {
            public void run() {
                simplePing(sessionId, name, editText.getText().toString());
            }
        });
    }

    public void FoundNameCallback(String busName)
    {
        Log.e("SimpleClient", String.format("Found name %s", busName));
        Message msg = handler.obtainMessage(0);
        msg.arg1 = BUSNAMEITEM_FOUND;
        msg.obj = new BusNameItem(busName, true);
        handler.sendMessage(msg);
    }

    public void LostNameCallback(String busName)
    {
        Log.e("SimpleClient", String.format("Lost name %s", busName));
        for (int i = 0; i < busNameItemAdapter.getCount(); ++i) {
            BusNameItem item = busNameItemAdapter.getItem(i);
            if (busName.equals(item.getBusName())) {
                Message msg = handler.obtainMessage(0);
                msg.arg1 = BUSNAMEITEM_LOST;
                msg.obj = item;
                handler.sendMessage(msg);
                break;
            }
        }
    }

    public void DisconnectCallback(int sessionId, int reason)
    {
        Log.e("SimpleClient", String.format("Disconnect session %d. Reason = %d.", sessionId,reason));
        for (int i = 0; i < busNameItemAdapter.getCount(); ++i) {
            BusNameItem item = busNameItemAdapter.getItem(i);
            Log.e("SimpleClient", String.format("item.id=%d, sessionId=%d", item.getSessionId(), sessionId));
            if (item.getSessionId() == sessionId) {
                Message msg = handler.obtainMessage(0);
                msg.arg1 = BUSNAMEITEM_DISCONNECT;
                msg.obj = item;
                handler.sendMessage(msg);
                break;
            }
        }
    }

    public void hideInputMethod()
    {
        InputMethodManager inputManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        inputManager.hideSoftInputFromWindow(editText.getWindowToken(), 0);

    }
    static {
        System.loadLibrary("SimpleClient");
    }
}

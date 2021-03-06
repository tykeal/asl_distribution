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
package org.alljoyn.devmodules.common;

import android.util.Log;



// class for keeping track of file transfer statistics
public class TransferStatistics {

	private static final String TAG = "TransferStatistics";

	// variables to hold running stats
	private String  mFilename ;
	private int     mCount ;
	private int     mBufSize ;
	private int     mFileSize ;
	private double  mOldM, mNewM, mOldS, mNewS ;
	private double  mStartTime, mEndTime ;
	private double  mBuffTxTime;
	private double  mMeanRate, mVariance ;
	private boolean mResult ;

	private TransferStatistics(){
		// no implementation, just making private to force supply of filename
	}

	// Constructor
	public TransferStatistics(String filename){
		mFilename = filename;
		// strip path info, if present
		if (mFilename.contains("/")){
			mFilename = mFilename.substring(mFilename.lastIndexOf("/")+1);
		}
		mCount = 0;
		mBufSize = 0 ;
		mFileSize = 0;
		mOldM = mNewM = mOldS = mNewS = 0.0;
		mStartTime = mEndTime = 0.0 ;
		mMeanRate = mVariance = 0.0 ;
		mBuffTxTime = 0.0;
		mResult = false;
	}

	// set the file size to be transferred
	public void setFileSize(int filesize){
		mFileSize = filesize;
	}

	// set the buffer size (in bytes) for transfers
	public void setBufferSize(int bufsize){
		mBufSize = bufsize;
	}

	// sets the time for the start of the file transfer
	public void setStartTime (double start){
		mStartTime = start;
	}

	// sets the time for the end of the file transfer
	public void setEndTime (double end){
		mEndTime = end;
	}

	// add a buffer transfer time to the statistics
	public void addBufferTime (double btime){
		mCount++;
		mBuffTxTime += btime;

		// update running average and std dev
		if (mCount==1){
			mOldM = mNewM = btime;
			mOldS = 0.0 ;
		} else {
			mNewM = mOldM + (btime - mOldM) / mCount;
			mNewS = mOldS + (btime - mOldM) * (btime - mNewM);

			mOldM = mNewM ;
			mOldS = mNewS ;
		}

		mMeanRate = ((mBufSize*8) / mNewM) * 1000.0;
		mVariance = (mCount>1) ? (mNewS/(mCount-1)): 0.0 ;
	}

	// Set the Mean Rate. Really only used to set up class from stored values
	public void setMeanRate(double mean){
		mMeanRate = mean;
	}
	
	// Set the Standard Deviation. Really only used to set up class from stored values
	public void setStdDev(double stddev){
		mVariance = stddev * stddev ;
	}

	// sets the result (pass/fail) of the file transfer
	public void setResult (boolean result){
		mResult = result;
	}

	// get the filename for this set of statistics
	public String getFilename(){
		return mFilename;
	}

	// get the file size (in bytes)
	public int getFileSize(){
		return mFileSize ;
	}

	// set the buffer size (in bytes) for transfers
	public int getBufferSize(){
		return mBufSize ;
	}

	// get the (start) time of the transaction
	public double getStartTime(){
		return mStartTime;
	}

	// get the result (pass/fail) of the transaction
	public boolean getResult(){
		return mResult;
	}

	// get the time taken to transfer the entire file
	public double getFileTxTime(){
		return (mStartTime < mEndTime) ? (mEndTime - mStartTime) : 0.0 ;
	}

	// get the time taken to transfer the file segments (i.e. minus overhead)
	public double getBufferTxTime(){
		return mBuffTxTime ;
	}

	// get the time taken for overhead
	public double getOverheadTime(){
		return getFileTxTime() - getBufferTxTime() ;
	}

	// get the number of buffers transferred
	public int getBufferCount(){
		return mCount;
	}

	// get the mean buffer transfer time
	public double getMeanTime(){
		return (mCount>0) ? mNewM : 0.0 ;
	}

	// get the mean buffer transfer rate (bits/sec)
	public double getMeanBufferRate(){
		return mMeanRate;
	}

	// get the mean file transfer rate (bits/sec)
	public double getMeanFileRate(){
		if (mCount>0){
			return ( ((mFileSize*8) / getFileTxTime()) * 1000.0);
		} else {
			return 0.0;
		}
	}

	// get (Sample) Variance
	public double getVariance(){
		return mVariance ;
	}

	// get the (Sample) Standard  Deviation
	public double getStdDev(){
		return Math.sqrt(getVariance());
	}

	// utility to dump the contents to log
	public void dump(){
		Log.d(TAG, "-------------------------");
		Log.d(TAG, "File Transfer Statistics:");
		Log.d(TAG, "  Name: "+getFilename());
		Log.d(TAG, "  File Size: "+getFileSize()+", Buffer size: "+getBufferSize());
		Log.d(TAG, "  Tx time: "+getFileTxTime()+", Buffer Tx time: "+getBufferTxTime()+", Overhead: "+getOverheadTime());
		Log.d(TAG, "  Num. Buffers: "+getBufferCount());
		Log.d(TAG, "  Mean Buffer rate: "+getMeanBufferRate()+", Mean File rate: "+getMeanFileRate());
		Log.d(TAG, "  Mean Buffer time: "+getMeanTime()+", Std. dev: "+getStdDev());
		Log.d(TAG, "  Success: "+getResult());
		Log.d(TAG, "-------------------------");
	}
}

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

package org.alljoyn.cops.filetransfer.data;

import java.util.Arrays;
import org.alljoyn.bus.annotation.Position;

/**
 * The file descriptor class is the main object that is passed around to remote
 * session peers and indicate valuable information regarding files that are
 * available for transfer. The file descriptor includes information regarding
 * who owns the file, the file name, the size of the file, the absolute path to the file (if
 * available) and the file ID. The file ID is the most important piece of data
 * because this is how most file transfers are initiated.
 * <p>
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public class FileDescriptor
{
	// Member Variables
	@Position(0)
	public String owner;
	
	@Position(1)
	public String sharedPath;
	
	@Position(2)
	public String relativePath;
	
	@Position(3)
	public String filename;
	
	@Position(4)
	public byte[] fileID;
	
	@Position(5)
	public int size;
	
	/*------------------------------------------------------------------------*
     * Constructor
     *------------------------------------------------------------------------*/
	/**
	 * FileDescriptor()
	 * creates a default instance of the file descriptor class. 
	 */
	public FileDescriptor()
	{
		//Intentionally left blank
	}
	
	/**
	 * FileDesriptor()
	 * provides a copy constructor for the File Descriptor class. This is needed so
	 * we do not over write data stored inside the Announcer's hash maps for announced
	 * and shared files.
	 * 
	 * @param copy  instance of the file descriptor object to copy
	 */
	public FileDescriptor(FileDescriptor copy)
	{
		owner = copy.owner;
		sharedPath = copy.sharedPath;
		relativePath = copy.relativePath;
		filename = copy.filename;
		fileID = copy.fileID;
		size = copy.size;
	}

	/**
	 * hashCode()
	 * overrides the default implementation of hashCode inherited from
	 * the Object class.
	 */
	@Override
	public int hashCode()
	{
		final int prime = 31;
		int result = 1;
		result = prime * result + Arrays.hashCode(fileID);
		result = prime * result
				+ ((filename == null) ? 0 : filename.hashCode());
		result = prime * result + ((owner == null) ? 0 : owner.hashCode());
		result = prime * result
				+ ((relativePath == null) ? 0 : relativePath.hashCode());
		result = prime * result
				+ ((sharedPath == null) ? 0 : sharedPath.hashCode());
		result = prime * result + size;
		return result;
	}	
	
	/**
	 * equals()
	 * overrides the default implementation of equals inherited from
	 * the Object class and ensures when can determine if the contents
	 * of two file descriptors are equal.
	 */
	@Override
	public boolean equals(Object obj)
	{		
		if (obj == null)
		{
			return false;
		}
		if (obj == this)
		{
			return true;
		}
		if (obj.getClass() != getClass())
		{
			return false;
		}
		
		FileDescriptor other = (FileDescriptor) obj;
		
		return owner.equals(other.owner) && sharedPath.equals(other.sharedPath) && relativePath.equals(other.relativePath)
				&& filename.equals(other.filename) && Arrays.equals(fileID, other.fileID) && size == other.size;
	}
}

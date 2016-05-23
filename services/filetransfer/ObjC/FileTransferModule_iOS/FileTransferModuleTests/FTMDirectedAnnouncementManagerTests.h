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

#import <SenTestingKit/SenTestingKit.h>
#import "FTMMockTransmitter.h"
#import "FTMFileAnnouncementReceivedDelegate.h"
#import "FTMUnannouncedFileRequestDelegate.h"
#import "TestProtocol.h"

@interface FTMDirectedAnnouncementManagerTests : SenTestCase <TestProtocol, FTMFileAnnouncementReceivedDelegate,                                                             FTMUnannouncedFileRequestDelegate>

//Test Protocol Functions
-(void)dataChunkSent: (FTMDataChunkAction *)dataChunkAction;
-(void)fileIDRequestSent: (FTMFileIDResponseAction *)fileIDResponseAction;
-(void)sendAnnouncementWithFileList: (NSArray *)fileList toPeer: (NSString *)peer andIsFileIDResponse: (BOOL)isFileIDResponse;
-(void)sendRequestDataUsingFileID: (NSData *)fileID startByte: (int)startByte length: (int)length andMaxChunkSize: (int)maxChunkSize toPeer: (NSString *)peer;
-(void)sendDataChunkUsingFileID: (NSData *)fileID startByte: (int)startByte chunkLength: (int)chunkLength andFileData: (NSData *)chunk toPeer: (NSString *)peer;
-(void)sendOfferFileWithFileDescriptor: (FTMFileDescriptor *)fd toPeer: (NSString *)peer;
-(void)sendAnnouncementRequestToPeer: (NSString *)peer;
-(void)sendStopDataXferForFileID: (NSData *)fileID toPeer: (NSString *)peer;
-(void)sendXferCancelledForFileID: (NSData *)fileID toPeer: (NSString *)peer;
-(void)sendRequestOfferForFileWithPath: (NSString *)filePath toPeer: (NSString *)peer;

@end

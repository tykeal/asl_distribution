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
//

#import "GetAboutCallViewController.h"
#import "AJNMessageArgument.h"
#import "alljoyn/about/AJNAboutClient.h"
#import "alljoyn/about/AJNAboutDataConverter.h"
#import "ViewController.h"
#import "GetAboutCallViewController.h"
#import "alljoyn/config/AJCFGConfigLogger.h"

static NSString * const CLIENTDEFAULTLANG=@"";

@interface GetAboutCallViewController ()
@property (weak, nonatomic) IBOutlet UILabel *lblVersion;
@property (weak, nonatomic) IBOutlet UILabel *lblAboutLanguage;
@property (weak, nonatomic) IBOutlet UITextView *txtViewBusObjectDesc;
@property (weak, nonatomic) IBOutlet UITextView *txtViewAboutMap;
@property (weak, nonatomic) IBOutlet UIButton *optionsButton;

@property (strong, nonatomic) AJNMessageArgument *supportedLanguagesMsgArg;
@property (nonatomic) AJNSessionId sessionId;
@property (nonatomic) UIAlertView *alertBusName;
@property (nonatomic) UITextField *alertChooseLanguage;
@property (nonatomic) UIAlertView *alertAnnouncementOptions;
@property (nonatomic) UIAlertView *alertNoSession;

@end

@implementation GetAboutCallViewController

- (void)prepareAlerts
{
	//  busNameAlert.tag = 1
	self.alertBusName = [[UIAlertView alloc] initWithTitle:@"Set language"
	                                               message:@"" delegate:self
	                                     cancelButtonTitle:@"Cancel"
	                                     otherButtonTitles:@"OK", nil];
	self.alertBusName.alertViewStyle = UIAlertViewStylePlainTextInput;
	self.alertBusName.tag = 1;
	self.alertChooseLanguage = [self.alertBusName textFieldAtIndex:0]; //connect the UITextField with the alert
    
	//  announcementOptionsAlert.tag = 2
	self.alertAnnouncementOptions = [[UIAlertView alloc] initWithTitle:@"Choose option:" message:@"" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Refresh", @"Set Language", nil];
	self.alertAnnouncementOptions.alertViewStyle = UIAlertViewStyleDefault;
	self.alertAnnouncementOptions.tag = 2;
    
	//  alertNoSession.tag = 3
	self.alertNoSession = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Session is not connected, check the connection and reconnect." delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
	self.alertNoSession.alertViewStyle = UIAlertViewStyleDefault;
	self.alertNoSession.tag = 3;
}

- (IBAction)TouchUpInsideRefreshandSetLanguage:(UIButton *)sender
{
	[self.alertAnnouncementOptions show];
}

- (bool)isValidLanguage:(NSString *)inputLanguage
{
	bool found = false;
	const ajn::MsgArg *stringArray;
	size_t fieldListNumElements;
	QStatus status = [self.supportedLanguagesMsgArg value:@"as", &fieldListNumElements, &stringArray];
	if (status == ER_OK) {
		for (size_t i = 0; i < fieldListNumElements; i++) {
			char *tempString;
			stringArray[i].Get("s", &tempString);
			if ([inputLanguage isEqualToString:@(tempString)]) {
				found = true;
				break;
			}
		}
	}
	return found;
}

//  Get the user's input from the alert dialog
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	switch (alertView.tag) {
		case 1: // busNameAlert
		{
			if (buttonIndex == 1) { //user pressed OK
                if ([self.alertChooseLanguage.text isEqualToString:@""]) {
                    self.alertChooseLanguage.text = [AJNAboutDataConverter messageArgumentToString:[self.clientInformation.announcement aboutData][@"DefaultLanguage"]];
                }
				if (![self isValidLanguage:self.alertChooseLanguage.text]) {
					[[[UIAlertView alloc] initWithTitle:@"Error" message:@"Requested language is not supported" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil] show];
					return;
				}
                
				self.clientInformation.currLang = self.alertChooseLanguage.text;
                
				[self UpdateCallViewInformation];
			}
			else {
				// cancel
			}
		}
            break;
            
		case 2: //announcementOptionsAlert
		{
			if (buttonIndex == 1) {
				//refresh
                
				[self UpdateCallViewInformation];
			}
			else if (buttonIndex == 2) {
				self.alertBusName.message = [NSString stringWithFormat:@"Available:%@", [AJNAboutDataConverter messageArgumentToString:self.supportedLanguagesMsgArg]];
				[self.alertBusName show];
			}
		}
            break;
            
		case 3: //NoSessionAlert
		{
		}
            break;
            
		default:
             NSLog(@"[%@] [%@] alertView.tag is wrong", @"ERROR", [[self class] description]);

			break;
	}
} //  alert view:clickedButtonAtIndex:

- (void)UpdateCallViewInformation
{
	self.lblVersion.text = [NSString stringWithFormat:@"%u", [self.clientInformation.announcement version]];
    
	if (!self.sessionId) {
		//create sessionOptions
		AJNSessionOptions *opt = [[AJNSessionOptions alloc] initWithTrafficType:kAJNTrafficMessages supportsMultipoint:false proximity:kAJNProximityAny transportMask:kAJNTransportMaskAny];
		//call joinSession
		self.sessionId = [self.clientBusAttachment
		                  joinSessionWithName:[self.clientInformation.announcement busName]
                          onPort:[self.clientInformation.announcement port]
                          withDelegate:(nil) options:opt];
	}
    
	if (self.sessionId == 0 || self.sessionId == -1) {
         NSLog(@"[%@] [%@] Failed to join session. sid=%u", @"DEBUG", [[self class] description],self.sessionId);

		[self.alertNoSession show];
	}
	else {
		NSMutableDictionary *aboutData;
		NSMutableDictionary *objDesc;
        
        
		AJNAboutClient *ajnAboutClient = [[AJNAboutClient alloc] initWithBus:self.clientBusAttachment];
        
        QStatus qStatus = [ajnAboutClient aboutDataWithBusName:[self.clientInformation.announcement busName] andLanguageTag:self.clientInformation.currLang andAboutData:&aboutData andSessionId:self.sessionId];
        
        if (qStatus != ER_OK) {
            UIAlertView *errorAlert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Calling the about method returned with an error" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
            
            [errorAlert show];
        }
        else {
            [ajnAboutClient objectDescriptionsWithBusName:[self.clientInformation.announcement busName] andObjectDescriptions:&objDesc andSessionId:self.sessionId];
            
            NSLog(@"[%@] [%@] AboutData:  %@", @"DEBUG", [[self class] description], [AJNAboutDataConverter aboutDataDictionaryToString:aboutData]);
            
            NSLog(@"[%@] [%@] objectDescriptions:  %@", @"DEBUG", [[self class] description], [AJNAboutDataConverter objectDescriptionsDictionaryToString:objDesc]);

            self.supportedLanguagesMsgArg = aboutData[@"SupportedLanguages"];
            
            
            self.lblAboutLanguage.text = self.clientInformation.currLang;
            self.txtViewAboutMap.text = [AJNAboutDataConverter aboutDataDictionaryToString:aboutData];
            self.txtViewBusObjectDesc.text = [AJNAboutDataConverter objectDescriptionsDictionaryToString:objDesc];
        }
    }
}


- (void)viewDidLoad
{
	[super viewDidLoad];
    
	[self prepareAlerts];
    
	[self UpdateCallViewInformation];
}


- (void)viewWillDisappear:(BOOL)animated
{
	[self.clientBusAttachment leaveSession:self.sessionId];
    
	[super viewWillDisappear:animated];
}

@end

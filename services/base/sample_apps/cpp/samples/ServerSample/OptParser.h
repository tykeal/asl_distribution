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

#ifndef OPTPARSER_H_
#define OPTPARSER_H_

#include <map>
#include <qcc/String.h>

/**
 * Class to parse arguments
 */
class OptParser {
  public:
    /**
     * ParseResultCode
     */
    enum ParseResultCode {
        PR_OK, PR_EXIT_NO_ERROR, PR_INVALID_OPTION, PR_MISSING_OPTION, PR_INVALID_APPID
    };

    /**
     * OptParser
     * @param argc
     * @param argv
     */
    OptParser(int argc, char** argv);

    /**
     * ParseResult
     * @return
     */
    ParseResultCode ParseResult();

    /**
     * GetFactoryConfigFile
     * @return
     */
    qcc::String const& GetFactoryConfigFile() const;

    /**
     * GetConfigFile
     * @return
     */
    qcc::String const& GetConfigFile() const;

    /**
     * GetAppId
     * @return
     */
    qcc::String const& GetAppId() const;

  private:
    int argc;
    char** argv;

    bool IsAllHex(const char* data);

    void PrintUsage();

    qcc::String factoryConfigFile;
    qcc::String configFile;
    qcc::String appGUID;
};

#endif /* OPTPARSER_H_ */

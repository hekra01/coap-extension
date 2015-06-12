/****************************************************************************
**
** Copyright © 1992-2014 Cisco and/or its affiliates. All rights reserved.
** All rights reserved.
**
** $CISCO_BEGIN_LICENSE:APACHE$
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
** http://www.apache.org/licenses/LICENSE-2.0
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** $CISCO_END_LICENSE$
**
****************************************************************************/
#include "extension/coap_instance.h"


#include <stdio.h>
#include <stdlib.h>
#include <string>


char *pDebugEnv = NULL;

CoapInstance::CoapInstance() {
    pDebugEnv = getenv("COAP_DEBUG");
}

CoapInstance::~CoapInstance() {
}

void CoapInstance::HandleMessage(const char* message) {
  std::string resp = PrepareMessage(message);
  PostMessage(resp.c_str());
}

void CoapInstance::HandleSyncMessage(const char* message) {
  std::string resp = PrepareMessage(message);
  SendSyncReply(resp.c_str());
}

static std::string executeLinuxCmd(const char *linuxCommand)
{
  FILE *pFile = NULL;

  std::string reponse = "";

  if (pDebugEnv != NULL)
    printf("[EXECUTE >>]: %s\n", linuxCommand);

  pFile = popen(linuxCommand, "r");
  if (pFile != NULL)
  {
      while (1)
      {
          char *line;
          char buffer[1024];
          line = fgets(buffer, sizeof(buffer), pFile);
          if (line == NULL) break;
        
          //printf("EXECUTE RESPONSE: %s", line);
          reponse = reponse + std::string(line);  
      }

      pclose(pFile);
  }

  if (pDebugEnv != NULL)
    printf("[RSP <<]: %s", reponse.c_str());

  return reponse;
}

std::string CoapInstance::ExecuteCommand(const picojson::value& msg) const {

  std::string commandPath   = msg.get("path").to_str();
  std::string commandParams = msg.get("params").to_str();
  std::string fullCommand = commandPath + " " + commandParams;

  std::string reponse = executeLinuxCmd(fullCommand.c_str());

  return reponse;
}

std::string CoapInstance::PrepareMessage(const std::string & message) const {

  const char *msg = message.c_str();
  std::string resp = "";

  if (pDebugEnv != NULL)
    printf("CoapInstance::PrepareMessage: %s\n", msg);

  picojson::value v;
  std::string error;

  picojson::parse(v, msg, msg + strlen(msg), &error);
  if (!error.empty()) {
    std::cout << "Ignoring message.\n";
    return resp;
  }

  std::string cmd = v.get("cmd").to_str();
  

  if (cmd == "ExecuteCommand")
  {
      resp = ExecuteCommand(v);
  }

  return resp;
}


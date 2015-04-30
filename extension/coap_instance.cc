#include "extension/coap_instance.h"


#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <sstream>
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


std::vector<std::string> splitstdstring(const std::string &inputstring, char delimiter)
{
    //printf("splitstdstring: %s\n", inputstring.c_str());

    std::vector<std::string> elements;
    std::string word;
    std::stringstream inputstream(inputstring);

    while( getline(inputstream, word, delimiter))
        elements.push_back(word);

    return elements;
}



std::string executeLinuxCmd(const char *linuxCommand)
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


std::string commandCmdPath = "/usr/lib/examples/./coap-client";
std::string commandCmdParams = " -B 2"; // Break 2s
std::string deviceIP = "coap://224.0.1.187";


std::string CoapInstance::PrepareMessage(std::string msg) const {

  if (pDebugEnv != NULL)
    printf("CoapInstance::PrepareMessage: %s\n", msg.c_str());

  unsigned int i;
  std::vector<std::string> params = splitstdstring(msg, ';');

  if (params.size())
  {
      for(i = 0; i < params.size(); i++)
      {
          //printf("param[%d]=%s\n", i, params[i].c_str());
      }

      if (params.size() >= 4)
      {
          deviceIP = params[0];

          if (params[1] == "put")
          {
              std::string deviceString = params[2];
              std::string stateString = params[3];

              std::string command = commandCmdPath + commandCmdParams + " -e " +  stateString + " -m put " + deviceIP +"/" + deviceString;
              executeLinuxCmd(command.c_str());
          }
          else if (params[1] == "get")
          {
              std::string deviceString = params[2];

              std::string command = commandCmdPath + commandCmdParams + " " + deviceIP + "/" + deviceString;
              std::string reponse = executeLinuxCmd(command.c_str());
              return reponse;   
          }
      }
      else if (params.size() >= 3)
      {
          deviceIP = params[0];

          if (params[1] == "get")
          {
              std::string deviceString = params[2];

              std::string command = commandCmdPath + commandCmdParams + " " + deviceIP + "/" + deviceString;
              std::string reponse = executeLinuxCmd(command.c_str());
              return reponse;
          }
      }
  }


  return "You said: " + msg;
}


#ifndef COAP_INSTANCE_H_
#define COAP_INSTANCE_H_

#include <string>

#include "common/extension.h"

class CoapInstance : public common::Instance {
 public:
  CoapInstance();
  ~CoapInstance();

  // common::Instance implementation
  void HandleMessage(const char* message);
  void HandleSyncMessage(const char* message);

 private:
  std::string PrepareMessage(std::string msg) const;
};

#endif  // ECHO_INSTANCE_H_


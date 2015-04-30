#ifndef COAP_EXTENSION_H_
#define COAP_EXTENSION_H_

#include "common/extension.h"

class CoapExtension : public common::Extension {
 public:
  CoapExtension();
  virtual ~CoapExtension();

 private:
  // common::Extension implementation.
  virtual common::Instance* CreateInstance();
};

#endif  // COAP_EXTENSION_H_



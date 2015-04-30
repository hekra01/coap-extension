#include "extension/coap_extension.h"
#include "extension/coap_instance.h"

common::Extension* CreateExtension() {
  return new CoapExtension();
}

extern const char kSource_coap_api[];

CoapExtension::CoapExtension() {
  SetExtensionName("coap");
  SetJavaScriptAPI(kSource_coap_api);
}

CoapExtension::~CoapExtension() {}

common::Instance* CoapExtension::CreateInstance() {
  return new CoapInstance();
}


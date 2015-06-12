COAP_CFLAGS=$(CFLAGS) -fPIC -Wall
SOURCES=extension/coap_extension.cc extension/coap_instance.cc extension/coap_api.cc common/extension.cc

all: libcoap-extension.so xpk

coap_api.cc:
	python tools/generate_api.py extension/coap_api.js kSource_coap_api extension/coap_api.cc

libcoap-extension.so: prepare coap_api.cc
	$(CC) $(COAP_CFLAGS) -shared -o build/libcoap-extension.so \
	$(SYSROOT_FLAGS) -I./ $(SOURCES)

prepare:
	mkdir -p build

install: libcoap-extension.so
	install -D build/libcoap-extension.so \
	$(DESTDIR)/$(PREFIX)/lib/tizen-extensions-crosswalk/libcoap-extension.so
	install -D build/xwalk-coap-extension-demo.xpk \
	$(DESTDIR)/$(PREFIX)/share/widget_demo/xwalk-coap-extension-demo.xpk

clean:
	rm -Rf build
	rm extension/coap_api.cc

xpk: tools/mykey.pem
	openssl genrsa -out tools/mykey.pem 1024
	./make_xpk.sh test/ tools/mykey.pem xwalk-coap-extension-demo
	mv xwalk-coap-extension-demo.xpk build/

.PHONY: all prepare clean

# coap-extension
Tizen Crosswalk extension for libCoAP

This projects provides a Tizen-Crosswalk extension for libCoAP-4.1.1
The extension uses coap-client from libCoAP. 
libCoAP for Tizen is avalaible here: https://github.com/cisco-open-source/libcoap. (At this time coap-client is not provided by Iotivity)

# Install
Build rpm
``` shell
$ gbs build --arch armv7hl platform/framework/web/coap-extension/
```
This will create 2 rpms
* coap-extension-0.1-1.armv7hl.rpm: The xwalk extension libraries
* coap-extension-demo-0.1-1.noarch.rpm: A demo application
zypper in the rpms 

# Demo application
After installing coap-extension-demo-0.1-1.noarch rpm, launch the demo XPK application:
```shell
$ xwalk-launcher file:///usr/share/demos/coap-extension-demo/index.html
```
The demo application has been packaged with:
```shell
$ openssl genrsa -out tools/mykey.pem 1024
$ ./make_xpk.sh test/ tools/mykey.pem xwalk-coap-extension-demo
```
To install and launch
```shell
$ su - guest -c "/usr/bin/pkgcmd -i -q -t xpk -p /usr/share/demos/coap-extension-demo/xwalk-coap-extension-demo.xpk"
$ ail_list
$ xwalk-launcher xwalk.<APPID>
```
To uninstall:
```shell
$ su - guest -c "/usr/bin/pkgcmd -u -t xpk -q <appid>
```
Demo video available here: http://cisco-open-source.github.io/coap-extension/index.html


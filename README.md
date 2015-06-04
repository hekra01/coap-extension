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
Install coap-extension-demo-0.1-1.noarch.rpm to get the demo xpk
```shell
root# zypper in coap-extension-demo
root# su - guest
guest# pkgcmd -i -t xpk -q -p /usr/share/widget_demo/xwalk-coap-extension-demo.xpk
guest# ail_list
guest# xwalk-launcher xwalk.<appid>
```
To uninstall:
```shell
guest# "pkgcmd -u -t xpk -q -n <appid>
```
Demo video here: http://cisco-open-source.github.io/coap-extension/index.html


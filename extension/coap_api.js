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
var coapListener = null;

extension.setMessageListener(function(msg) {
  if (coapListener instanceof Function) {
    coapListener(msg);
  };
});

exports.echoAsync = function (msg, callback) {
  coapListener = callback;
  extension.postMessage(msg);
};

exports.echoSync = function (msg) {
  console.log("echoSync");
  return extension.internal.sendSyncMessage(msg);
};

exports.setDevice = function(destaddr, devicename, state, callback) {
  console.log("setDevice");
  coapListener = callback;

  var options = {
    dest: destaddr,
    cmd: "put",
    resource: devicename,
    value: state
  };

  //var message = JSON.stringify(options);
  var message = destaddr + ";" + "put;"+ devicename + ";" + state;

  //return extension.internal.sendSyncMessage(message); // SYNC
  extension.postMessage(message); // ASYNC
};

exports.getDevice = function(destaddr, devicename, callback) {
  console.log("getDevice");
  coapListener = callback;

  var options = {
    dest: destaddr,
    cmd: "get",
    resource: devicename
  };

  //var message = JSON.stringify(options);
  var message = destaddr + ";" + "get;"+ devicename + ";";

  extension.postMessage(message); // ASYNC
};

exports.getDeviceSync = function(destaddr, devicename) {
  console.log("getDeviceSync");
 
  var options = {
    dest: destaddr,
    cmd: "get",
    resource: devicename
  };

  //var message = JSON.stringify(options);
  var message = destaddr + ";" + "get;"+ devicename + ";";

  return extension.internal.sendSyncMessage(message); // SYNC
};







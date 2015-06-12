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
var coapDefaultCmdPath = "/usr/lib/examples/./coap-client";
var coapDefaultCmdParams = "-B 2 -p 5683";

extension.setMessageListener(function(msg) {
  if (coapListener instanceof Function) {
    coapListener(msg);
  };
});

exports.handleMessageAsync = function(msg, callback) {
  coapListener = callback;
  extension.postMessage(msg);
};

exports.handleMessageSync = function(msg) {
  return extension.internal.sendSyncMessage(msg);
};

exports.initCommandsAndParams = function(cmdPath, cmdDefaultParams) {
    coapDefaultCmdPath = cmdPath;
    coapDefaultCmdParams = cmdDefaultParams;
};

exports.executeCommmand = function(cmdPath, cmdParams) {

  var msg = {
    'cmd': 'ExecuteCommand',
    'path': cmdPath,
    'params': cmdParams
  };

  console.log("executeCommmand " + msg);

  var result = extension.internal.sendSyncMessage(JSON.stringify(msg));

  return result;
};

exports.setDevice = function(destaddr, devicename, state, callback) {
  coapListener = callback;

  var params = coapDefaultCmdParams + " -e " + "\"" + state + "\"" + " -m put " + destaddr + "/" + devicename;

  console.log("setDevice " + params);

  coap.executeCommmand(coapDefaultCmdPath, params);
};

exports.getDevice = function(destaddr, devicename) {

  var params = coapDefaultCmdParams + " -m get " + destaddr + "/" + devicename;

  console.log("getDevice " + params);

  return coap.executeCommmand(coapDefaultCmdPath, params);
};








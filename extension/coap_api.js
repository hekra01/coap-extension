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







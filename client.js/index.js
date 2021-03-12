var net = require('net');
var protobuf = require("protobufjs");

var HOST = '127.0.0.1';
var PORT = 12345;

var client = new net.Socket();
client.connect(PORT, HOST, function () {
    console.log('CONNECTED TO: ' + HOST + ':' + PORT);
    // client.write(buff);
    run();
});

client.on('data', function (data) {
    console.log('Data: ' + data);
    // var telegram = protobuf.lookupType("labs_proto.telegram");
    protobuf.load("msg.proto", function (err, root) {
    if (err) throw err;
    var telegram = root.lookupType("labs_proto.telegram");

    var msg = telegram.decode(data);
    console.log(msg);
    run();
    })
    // client.destroy();
});

client.on('close', function () {
    console.log('Connection closed');
});


function run() {
    protobuf.load("msg.proto", function (err, root) {
        if (err) throw err;
        var telegram = root.lookupType("labs_proto.telegram");
        var payload = { code: 0, msg: " - hello world! | the best world! <" };

        // var errMsg = telegram.verify(payload);
        // if (errMsg) throw Error(errMsg);

        // for (var i=0; i < 2; ++i) {
            payload.code = 3;
            console.log(payload);
            var message = telegram.create(payload);
            var b = telegram.encode(message).finish();
            client.write(b);
        // }
        // client.destroy();
    });
}


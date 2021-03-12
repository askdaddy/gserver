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

        for (var i=0; i < 9000000; ++i) {
            payload.code = i;
            console.log(payload);
            var message = telegram.create(payload);
            var b = telegram.encode(message).finish();
            client.write(b);
        }
        // client.destroy();
    });
}


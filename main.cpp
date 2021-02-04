#include <iostream>
#include <server_net.h>

using namespace std;

int main() {
    net::ServerNet server;
    server.Start("0.0.0.0",12345);
//    boost::any foo = 42;
//    foo.clear();

    cout << "Hello world!" << endl;
    return 0;
}

#include <iostream>

//#include <server_net.h>
#include <test_buffer.h>

//using namespace net;
int main() {
//    ServerNet server;

//    server.Start("0",12400);
    TestBuffer t("0.0.0.0",12400);


    std::cout << "In the end." << std::endl;
    return 0;
}

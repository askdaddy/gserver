#include <iostream>

//#include "server_net.h"
//using namespace net;
#include "test_buffer.h"

int main() {
//    ServerNet::GetInstancePtr()->Start("0",24000);

    TestBuffer tb("0.0.0.0", 24000);

    std::cout << "In the end." << std::endl;
    return 0;
}

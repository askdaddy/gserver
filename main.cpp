#include <iostream>

#include "server_net.h"
using namespace net;
int main() {
    ServerNet::GetInstancePtr()->Start("0",24000);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

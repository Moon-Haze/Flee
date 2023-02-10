#include "QQClient.h"
#include <iostream>

int main(int argc, char** argv) {
    using namespace Flee;
    QQClient client(2163973016);
    std::cout << "client create" << std::endl;
    client.login();
    return 0;
}
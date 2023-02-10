/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-10 18:14
 * @FilePath: \Flee\test\Flee_test.cpp
 * @Description:
 */

#include "ecdh.h"
#include <iostream>

int main() {

    Flee::ECDH ecdh = Flee::ECDH::generateKeyPair();
    std::cout << ecdh.getPrivateKey() << std::endl;
    std::cout << ecdh.getPublicKey() << std::endl;
    return 0;
}

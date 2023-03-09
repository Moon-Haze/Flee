/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-05 18:58
 * @FilePath: \Flee\test\Flee_test.cpp
 * @Description:
 */

#include "ByteArray.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    auto image = Flee::ByteArray::fromHex(
        "89 50 4E 47 0D 0A 1A 0A 00 00 00 0D 49 48 44 52 00 00 00 87 00 00 00 87 01 00 "
        "00 00 00 14 9C 77 A7 00 00 00 09 70 48 59 73 00 00 0B 13 00 00 0B 13 01 00 9A "
        "9C 18 00 00 01 B2 49 44 41 54 48 89 DD D6 31 AE E4 20 0C 00 50 47 14 74 C9 05 "
        "90 7C 0D 3A AE 14 2E 90 64 2E 30 B9 12 1D D7 40 E2 02 A4 A3 40 F8 9B 89 FE 7E "
        "69 9B F1 6C B5 FA 28 4D 5E 41 8C ED 38 01 FA 7B C1 2F 91 02 E0 43 3E 20 1F D6 "
        "00 A0 50 2E 6A BE 22 55 B3 04 B3 93 58 82 F1 71 6C C2 B2 EA 0F 64 B5 74 52 5B "
        "62 FB 48 38 E6 33 E0 13 CC 07 42 6D D3 EA 09 6D B6 3F A7 78 2B 23 3F D1 DC D7 "
        "4F C6 DE 09 2F C6 3D A6 CD E1 9F EA BC 95 AE CD 12 61 27 E0 A7 AF AF 7D 44 62 "
        "B1 E8 DC 6D F2 11 29 4A A5 68 AE 3B 27 36 77 D7 16 12 8B C5 A7 C3 0E 69 86 7C "
        "DE 3D 26 90 EE 92 AF EA A9 A9 38 3E 2F 4A 45 E7 47 C4 2B 9A 3D 9A 0D A4 52 B4 "
        "D9 2C 3B 5E 94 29 48 85 2A 9E A3 1C 69 83 36 55 A9 5C 15 A6 A0 8A 4D 53 05 DE "
        "50 28 5D 13 8D 80 47 CF CC 16 85 C2 67 9C 22 CC 9A 9B B9 81 5C 02 87 6D 66 9D "
        "56 6D 7C 25 A1 14 CD B5 33 9E 54 B7 B0 88 A5 73 D1 75 3E 23 AC 7A E4 4A 28 DC "
        "63 4B 44 DE C4 F3 61 83 58 6C 66 04 C7 9D C9 1D 26 97 E4 89 A3 C5 C3 A6 D9 92 "
        "50 BA 53 8F AA 28 34 E0 F7 34 4A E5 AA 6D 0F 3C E8 C0 F3 48 B9 6B 21 90 AE 55 "
        "01 75 46 75 D8 D7 80 95 C9 C5 01 C7 CC 91 6F 0E A6 28 15 5E 17 27 33 70 2D F0 "
        "AA 52 19 B3 8E D2 66 EF 71 27 15 9E AB 7B 80 D9 A5 79 BC 74 24 15 9E E1 84 07 "
        "17 71 D4 11 E5 B2 BD EA B8 C1 18 0E 72 59 EF 99 10 D4 E1 C4 42 6D 75 E3 93 51 "
        "9C A2 4A 42 E1 FC F0 28 E0 DB EE CC FE 9D D5 B7 F2 6F FF 00 FF BB 7C 01 CB 95 "
        "A5 5F 3E 8F 3C E7 00 00 00 00 49 45 4E 44 AE 42 60 82");
    std::ofstream ofs;
    ofs.open("test.png", std::ios::binary);
    if(ofs.is_open()) {
        ofs << image;
        // ofs.write(( char* )image.data(), image.size());
    }
    ofs.close();
    return 0;
}
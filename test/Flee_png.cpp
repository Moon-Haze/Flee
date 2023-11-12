/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-03-28 08:41
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-29 17:35
 * @FilePath: \Flee\test\Flee_png.cpp
 * @Description:
 */

#include "ByteArray.h"
#include "QRCode.h"
#include "lodepng.h"

#include <constants.h>
#include <cstddef>
#include <cstdint>

#include <iostream>
#include <spdlog/spdlog.h>
#include <sstream>

int main(int argc, char* argv[]) {

    auto image = Flee::ByteArray::fromHex(
        "89 50 4E 47 0D 0A 1A 0A 00 00 00 0D 49 48 44 52 00 00 00 87 00 00 00 87 01 00 "
        "00 00 00 14 9C 77 A7 00 00 00 09 70 48 59 73 00 00 0B 13 00 00 0B 13 01 00 9A "
        "9C 18 00 00 01 B8 49 44 41 54 48 89 DD 96 31 6E C4 20 10 45 67 E5 82 CE BE 00 "
        "12 D7 A0 E3 4A F6 05 BC DE 0B D8 57 A2 E3 1A 48 5C C0 74 14 88 C9 67 37 9B 48 "
        "69 76 36 55 14 E4 C2 7A 05 66 66 FE FF 98 F8 E7 A2 7F 42 4E A2 C5 A7 A6 D2 66 "
        "35 91 11 92 CC 75 29 B4 70 1D AD BE B2 98 78 BD 04 B3 5B 3D 79 3D AB 37 C8 EC "
        "F4 54 F4 A8 EA 5B 64 F1 71 54 7C 14 FD 06 E1 7A F5 C3 6E 79 A7 EF 2A 5E 92 DE "
        "9F A0 1F CF 77 C7 5E 11 AC D3 71 53 71 74 E6 6B 3A 2F 49 53 7A 74 B5 B7 88 EA "
        "7C DF 47 42 38 A4 1C 86 9B 37 78 E1 22 25 A7 8B 33 FA 49 43 73 CF 2A 44 84 0F "
        "E6 E6 D0 D8 74 14 29 69 B6 5E CA B0 A9 74 3A 9A 02 0B C9 A9 CC A6 CC 81 29 78 "
        "3D 3E BE 2E 20 E8 CF 6A EB EC 4C E6 7B BD 52 62 76 85 03 C4 95 A0 34 29 E1 50 "
        "89 EA 54 88 1C AD 96 A5 84 D3 2D 98 5B 89 50 F5 68 8D 94 14 7D 09 B4 2A 68 2C "
        "92 98 9C 5D D2 30 0E 61 9F A5 B0 90 64 8E D8 04 E3 80 B0 27 31 B9 8B 79 38 3C "
        "4C 5A AF 4F 25 BC 26 38 2D 23 7F 60 37 9A 49 4A A0 E1 23 C4 8B 8F E4 52 73 2C "
        "25 28 93 D2 A6 06 2E F1 CA 52 D2 60 CF 02 59 76 71 3E BC 23 21 D9 D3 8A D4 0A "
        "3D 24 57 25 25 CD A5 A3 E7 CF 70 DA BA 3A 29 C9 01 99 90 F6 6E 22 C8 4C 4A B0 "
        "32 1C D7 B3 CB E4 22 25 F7 AC AB B0 C0 52 7A 98 0B C9 23 57 73 40 26 C0 74 2C "
        "25 FD BE A0 D1 D1 85 9F 55 C8 C8 6A 53 A3 88 DD 38 BC 41 66 DC 80 0A 07 18 36 "
        "27 26 8C 18 81 E3 30 47 08 86 85 04 FD 59 AD D9 5C 5C F8 33 49 24 E4 77 FF 00 "
        "7F 9D 7C 00 CC E0 99 D7 46 FE 7F EA 00 00 00 00 49 45 4E 44 AE 42 60 82");

    Flee::QRCode png;

    unsigned error = png.encode(image);

    if(error) {
        std::cout << "error " << error << ": " << lodepng_error_text(error)
                  << std::endl;
        return 0;
    }
    spdlog::info("\n{}", png.toString());
    return 0;
}

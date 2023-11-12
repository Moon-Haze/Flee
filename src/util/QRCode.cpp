/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-03-28 08:57
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-31 18:32
 * @FilePath: \Flee\src\util\QRCode.cpp
 * @Description:
 */
#include "QRCode.h"
#include "ByteArray.h"
#include "lodepng.h"
#include <constants.h>
#include <sstream>
#include <utility>

namespace Flee {

unsigned QRCode::encode(const ByteArray& input_data) {

    unsigned char* buffer;
    size_t         buffersize;

    LodePNGState state;
    lodepng_state_init(&state);
    state.info_raw.colortype = LCT_RGB;
    state.info_raw.bitdepth  = 8;
#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
    /*disable reading things that this function doesn't output*/
    state.decoder.read_text_chunks        = 0;
    state.decoder.remember_unknown_chunks = 0;
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
    unsigned error =
        lodepng_decode(&buffer, &width, &height, &state,
                       ( const unsigned char* )(input_data.data()), input_data.size());
    if(buffer && !error) {
        size_t buffersize = lodepng_get_raw_size(width, height, &(state.info_raw));
        data.clear();
        data.insert(data.begin(), ( Flee::Byte* )buffer,
                    ( Flee::Byte* )(buffer + buffersize));
    }
    std::free(buffer);
    lodepng_state_cleanup(&state);
    return error;
}

std::string QRCode::toString() const {
    const std::string symbol_fill = toConsole(u8"\u2584");
    std::stringstream line;
    for(uint64_t i = 36; i < height * 3 - 36; i += 18) {

        for(uint64_t j = 36; j < width * 3 - 36; j += 9) {
            auto r0 = data[i * width + j];
            auto r1 = data[i * width + j + (width * 3 * 3)];
            line << ((r1 == std::byte(0xff)) ? "\033[37m" : "\033[30m")
                 << ((r0 == std::byte(0xff)) ? "\033[47m" : "\033[40m") << symbol_fill;
        }
        line << "\033[0m" << std::endl;
    }
    auto test = toConsole("请使用 手机QQ 扫描二维码");
    line << "\033[30m"
         << "\033[47m"
         << "       " << test << "        "
         << "\033[0m\n"
         << "\033[30m"
         << "\033[47m"
         << "                                       "
         << "\033[0m";
    return line.str();
}
} // namespace Flee
#include "BuildPackage.h"

namespace Flee {
template class BuildPackage<uint16_t>;
template class BuildPackage<uint32_t>;

template <typename T>
BuildPackage<T>::BuildPackage(const ByteArray& data, T offset)
    : data(data), offset(offset) {
    static_assert(std::is_arithmetic<T>::value | std::is_same<T, char>::value
                      | std::is_same<T, std::byte>::value,
                  "T must be a numeric,char,byte type");
}

template <typename T>
BuildPackage<T>::BuildPackage(const std::string& data, T offset)
    : data(std::move(ByteArray::from(data))), offset(offset) {}

template <typename T>
T BuildPackage<T>::getOffset() const {
    return offset;
}

template <typename T>
const ByteArray& BuildPackage<T>::getData() const {
    return data;
}

template <typename T = uint16_t>
ByteArray& operator<<(ByteArray& array, const BuildPackage<T>& packet) {
    array << static_cast<T>(packet.getData().size() + packet.getOffset())
          << packet.getData();
    return array;
}

template ByteArray& operator<< <uint16_t>(ByteArray&                    array,
                                          const BuildPackage<uint16_t>& packet);

template ByteArray& operator<< <uint32_t>(ByteArray&                    array,
                                          const BuildPackage<uint32_t>& packet);
}
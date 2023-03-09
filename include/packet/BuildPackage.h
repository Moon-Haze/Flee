#ifndef FLEE_BUILDPACKAGE_H
#define FLEE_BUILDPACKAGE_H
#include "ByteArray.h"
#include <cstdint>


namespace Flee {
template <typename T = uint16_t>
class BuildPackage {
    /* data */
    ByteArray data;
    T         offset;

public:
    BuildPackage(const ByteArray& data, T offset = 0);

    BuildPackage(const std::string& data, T offset = 0);

    template <typename Z>
    BuildPackage(Z data, T offset = 0)
        : data(std::move(ByteArray::from<Z>(data))), offset(offset) {}

    T                getOffset() const;
    const ByteArray& getData() const;
};

template <typename T>
ByteArray& operator<<(ByteArray& array, const BuildPackage<T>& packet);

#define BuildPackageWithLength(data) BuildPackage<uint32_t>(data, 4)
} // namespace Flee

#endif // FLEE_BUILDPACKAGE_H
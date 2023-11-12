#ifndef FLEE_DEVICE_H
#define FLEE_DEVICE_H

#include "ByteArray.h"
#include <constants.h>
#include <cstddef>
#include <cstdint>
#include <string>

namespace Flee {

struct Version {

    ByteArray incremental = ByteArray::from<std::string>("5891938");
    ByteArray release     = ByteArray::from<std::string>("10");
    ByteArray codename    = ByteArray::from<std::string>("REL");
    int       sdk         = 29;

    Version() = default;

    Version(const Version& other)
        : incremental(other.incremental),
          release(other.release),
          codename(other.codename),
          sdk(other.sdk) {}
};

struct BaseDevice {
    std::string product;
    std::string device;
    std::string board;
    std::string brand;
    std::string model;
    std::string wifi_ssid;
    std::string bootloader;
    std::string android_id;
    std::string boot_id;
    std::string proc_version;
    std::string mac_address;
    std::string ip_address;
    std::string imei;
    uint32_t    incremental;

    BaseDevice() = default;

    BaseDevice(std::string product, std::string device, std::string board,
               std::string brand, std::string model, std::string wifi_ssid,
               std::string bootloader, std::string android_id, std::string boot_id,
               std::string proc_version, std::string mac_address,
               std::string ip_address, std::string imei, uint32_t incremental);

    BaseDevice(const BaseDevice& device);

    /**
     * @brief 通过 @a uin 创建一个 %BaseDevice
     *
     * @param uin qq id
     * @return BaseDevice 基本的设备class
     */
    static BaseDevice generateBaseDevice(uint64_t uin);

    /**
     * @brief 从json文件 @a filename 中读取一个BaseDevice
     *
     * @param filename json格式文件的路径
     * @return BaseDevice 基本的设备class
     */
    static BaseDevice loadBaseDevice(const std::string& filename);
};

class Device {
public:
    ByteArray   product;
    ByteArray   device;
    ByteArray   board;
    ByteArray   brand;
    ByteArray   model;
    ByteArray   wifi_ssid;
    ByteArray   bootloader;
    ByteArray   android_id;
    ByteArray   boot_id;
    ByteArray   proc_version;
    ByteArray   mac_address;
    ByteArray   ip_address;
    std::string imei;
    Version     version;
    // 以上都是 BaseDevice

    ByteArray   fingerprint;
    ByteArray   baseBand;
    ByteArray   simInfo    = ByteArray::from<std::string>("T-Mobile");
    ByteArray   osType     = ByteArray::from<std::string>("android");
    ByteArray   wifi_bssid = ByteArray::from<std::string>("02:00:00:00:00:00");
    ByteArray   imsi       = getRandomByteArray(16);
    ByteArray   apn        = ByteArray::from<std::string>("wifi");
    ByteArray   guid       = md5(ByteArray::from(imei) + mac_address);
    std::string qImei16;
    std::string qImei36;

    static Device getDevice(uint64_t uin, const std::string& filename = "");

    explicit Device(uint64_t uin);

    Device(const BaseDevice& basedevice);

    Device(ByteArray product, ByteArray device, ByteArray board, ByteArray brand,
           ByteArray model, ByteArray wifi_ssid, ByteArray bootloader,
           ByteArray android_id, ByteArray boot_id, ByteArray proc_version,
           ByteArray mac_address, ByteArray ip_address, std::string imei,
           ByteArray incremental);

    Device(const Device& other);

    friend std::ostream& operator<<(std::ostream& os, const Device& info);

    friend std::istream& operator>>(std::istream& os, Device& info);
};

}; // namespace Flee

#endif // FLEE_DEVICE_H
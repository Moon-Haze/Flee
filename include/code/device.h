#ifndef FLEE_DEVICE_H
#define FLEE_DEVICE_H

#include "ByteArray.h"
#include <constants.h>
#include <string>

namespace Flee {

class Version {
public:
    ByteArray incremental = toByteArray<std::string>("5891938");
    ByteArray release     = toByteArray<std::string>("10");
    ByteArray codename    = toByteArray<std::string>("REL");
    int       sdk         = 29;

    friend std::ostream& operator<<(std::ostream& os, const Version& version);

    friend std::istream& operator>>(std::istream& os, Version& version);
};

class Device {
public:
    ByteArray product    = toByteArray<std::string>("mirai");
    ByteArray device     = toByteArray<std::string>("mirai");
    ByteArray board      = toByteArray<std::string>("mirai");
    ByteArray brand      = toByteArray<std::string>("mamoe");
    ByteArray model      = toByteArray<std::string>("mirai");
    ByteArray wifi_ssid  = toByteArray<std::string>("<unknown ssid>");
    ByteArray bootloader = toByteArray<std::string>("unknown");
    ByteArray android_id =
        toByteArray<std::string>("OICQX." + getRandomIntString(8) + "."
                                 + getRandomIntString(3)); // OICQX.18667125.702
    ByteArray boot_id = toByteArray(generateUUID());
    ByteArray proc_version =
        toByteArray(std::string("Linux version 3.0.31-" + getRandomString(8)
                                + " (android-build@xxx.xxx.xxx.xxx.com)"));
    ByteArray   mac_address = toByteArray<std::string>("02:00:00:00:00:00");
    ByteArray   ip_address  = { Byte(0xc0), Byte(0xa8), Byte(0x1), Byte(0x7b) };
    std::string imei        = generateImei();
    Version     version;
    ByteArray   display     = android_id;
    ByteArray   fingerprint = toByteArray(
        std::string("mamoe/mirai/mirai:10/MIRAI.200122.001/")
        + getRandomIntString(7) + std::string(":user/release-keys"));
    ByteArray baseBand;
    ByteArray simInfo    = toByteArray<std::string>("T-Mobile");
    ByteArray osType     = toByteArray<std::string>("android");
    ByteArray wifi_bssid = toByteArray<std::string>("02:00:00:00:00:00");
    ByteArray imsiMd5;
    ByteArray apn  = toByteArray<std::string>("wifi");
    ByteArray guid = md5(display + ip_address);

    static Device getDevice(const std::string& filename = "");

    explicit Device() = default;

    Device(ByteArray product, ByteArray device, ByteArray board,
           ByteArray brand, ByteArray model, ByteArray wifi_ssid,
           ByteArray bootloader, ByteArray android_id, ByteArray boot_id,
           ByteArray proc_version, ByteArray mac_address, ByteArray ip_address,
           std::string imei, ByteArray incremental);

    Device(const Device& other);

    friend std::ostream& operator<<(std::ostream& os, const Device& info);

    friend std::istream& operator>>(std::istream& os, Device& info);

private:
    inline static std::string generateImei() {
        std::string temp = std::string("86") + getRandomIntString(12);
        return temp + char('0' + luhn(temp));
    }
};

}; // namespace Flee

#endif // FLEE_DEVICE_H
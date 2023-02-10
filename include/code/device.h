#ifndef FLEE_DEVICE_H
#define FLEE_DEVICE_H

#include "ByteArray.h"
#include <constants.h>
#include <string>

namespace Flee {

class Version {
public:
    ByteArray incremental = ByteArray::from<std::string>("5891938");
    ByteArray release     = ByteArray::from<std::string>("10");
    ByteArray codename    = ByteArray::from<std::string>("REL");
    int       sdk         = 29;

    friend std::ostream& operator<<(std::ostream& os, const Version& version);

    friend std::istream& operator>>(std::istream& os, Version& version);
};

class Device {
public:
    ByteArray product    = ByteArray::from<std::string>("mirai");
    ByteArray device     = ByteArray::from<std::string>("mirai");
    ByteArray board      = ByteArray::from<std::string>("mirai");
    ByteArray brand      = ByteArray::from<std::string>("mamoe");
    ByteArray model      = ByteArray::from<std::string>("mirai");
    ByteArray wifi_ssid  = ByteArray::from<std::string>("<unknown ssid>");
    ByteArray bootloader = ByteArray::from<std::string>("unknown");
    ByteArray android_id =
        ByteArray::from<std::string>("OICQX." + getRandomIntString(8) + "."
                                     + getRandomIntString(3)); // OICQX.18667125.702
    ByteArray boot_id      = ByteArray::from<std::string>(generateUUID());
    ByteArray proc_version = ByteArray::from<std::string>(
        std::string("Linux version 3.0.31-" + getRandomString(8)
                    + " (android-build@xxx.xxx.xxx.xxx.com)"));
    ByteArray   mac_address = ByteArray::from<std::string>("02:00:00:00:00:00");
    ByteArray   ip_address  = { Byte(0xc0), Byte(0xa8), Byte(0x1), Byte(0x7b) };
    std::string imei        = generateImei();
    Version     version;
    ByteArray   display     = android_id;
    ByteArray   fingerprint = ByteArray::from<std::string>(
        std::string("mamoe/mirai/mirai:10/MIRAI.200122.001/") + getRandomIntString(7)
        + std::string(":user/release-keys"));
    ByteArray baseBand;
    ByteArray simInfo    = ByteArray::from<std::string>("T-Mobile");
    ByteArray osType     = ByteArray::from<std::string>("android");
    ByteArray wifi_bssid = ByteArray::from<std::string>("02:00:00:00:00:00");
    ByteArray imsiMd5;
    ByteArray apn  = ByteArray::from<std::string>("wifi");
    ByteArray guid = md5(display + ip_address);

    static Device getDevice(const std::string& filename = "");

    explicit Device() = default;

    Device(ByteArray product, ByteArray device, ByteArray board, ByteArray brand,
           ByteArray model, ByteArray wifi_ssid, ByteArray bootloader,
           ByteArray android_id, ByteArray boot_id, ByteArray proc_version,
           ByteArray mac_address, ByteArray ip_address, std::string imei,
           ByteArray incremental);

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
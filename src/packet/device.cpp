
#include "device.h"
#include "ByteArray.h"
#include "ParsingException.h"
#include "constants.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/value.hpp>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <json/json.h>
#include <json/value.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace Flee {

BaseDevice::BaseDevice(std::string product, std::string device, std::string board,
                       std::string brand, std::string model, std::string wifi_ssid,
                       std::string bootloader, std::string android_id,
                       std::string boot_id, std::string proc_version,
                       std::string mac_address, std::string ip_address,
                       std::string imei, uint32_t incremental)
    : product(std::move(product)),
      device(std::move(device)),
      board(std::move(board)),
      brand(std::move(brand)),
      model(std::move(model)),
      wifi_ssid(std::move(wifi_ssid)),
      bootloader(std::move(bootloader)),
      android_id(std::move(android_id)),
      boot_id(std::move(boot_id)),
      proc_version(std::move(proc_version)),
      mac_address(std::move(mac_address)),
      ip_address(std::move(ip_address)),
      imei(std::move(imei)),
      incremental(std::move(incremental)) {}

BaseDevice::BaseDevice(const BaseDevice& device)
    : product(device.product),
      device(device.device),
      board(device.board),
      brand(device.brand),
      model(device.model),
      wifi_ssid(device.wifi_ssid),
      bootloader(device.bootloader),
      android_id(device.android_id),
      boot_id(device.boot_id),
      proc_version(device.proc_version),
      mac_address(device.mac_address),
      ip_address(device.ip_address),
      imei(device.imei),
      incremental(device.incremental) {}

BaseDevice BaseDevice::loadBaseDevice(const std::string& filename) {
    std::ifstream file(filename);
    std::string   json_data((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    // 将字符串解析为 JSON 对象
    boost::system::error_code errs;
    boost::json::value        root = boost::json::parse(json_data.c_str(), errs);
    if(errs) {
        spdlog::info("Failed to parse JSON data from file {}", filename);
    } else {
        spdlog::info("Load JSON data from file {}", filename);
        return BaseDevice(
            root.at("product").as_string().c_str(),
            root.at("device").as_string().c_str(), root.at("board").as_string().c_str(),
            root.at("brand").as_string().c_str(), root.at("model").as_string().c_str(),
            root.at("wifi_ssid").as_string().c_str(),
            root.at("bootloader").as_string().c_str(),
            root.at("android_id").as_string().c_str(),
            root.at("boot_id").as_string().c_str(),
            root.at("proc_version").as_string().c_str(),
            root.at("mac_address").as_string().c_str(),
            root.at("ip_address").as_string().c_str(),
            root.at("imei").as_string().c_str(), root.at("incremental").as_uint64());
    }
    return BaseDevice();
}
BaseDevice BaseDevice::generateBaseDevice(uint64_t uin) {
    ByteArray         hash = md5(std::to_string(uin));
    std::string       hex  = hash.toHex();
    std::stringstream ip_address;
    ip_address << "10.0." << ( uint8_t )(hash[10]) << '.' << ( uint8_t )(hash[11]);
    return BaseDevice(
        "MRS4S", "HIM188MOE", "MIRAI-YYDS", "OICQX", "Konata 2020",
        "TP-LINK-" + getRandomString(8), "U-boot",
        "OICQX." + getRandomNumString(8) + "." + getRandomNumString(3), generateUUID(),
        "Linux version 3.0.31-" + getRandomNumString(5)
            + " (android-build@xxx.xxx.xxx.xxx.com)",
        "02:00:00:00:00:00", ip_address.str(), generateImei(uin), 5891938);
}

Device Device::getDevice(uint64_t uin, const std::string& filename) {
    if((!filename.empty()) && boost::filesystem::exists(filename)) {

        return Device(BaseDevice::loadBaseDevice(filename));
    }
    spdlog::info("Device file ({}) isn't exists.", filename);
    std::ofstream ofs(filename);
    Device        device(BaseDevice::generateBaseDevice(uin));
    if(ofs.is_open()) {
        ofs << device;
    }
    ofs.close();
    spdlog::info("New device file created: {}", filename);
    return device;
}
Device::Device(uint64_t uin) : imei(std::move(generateImei(uin))) {

    fingerprint << this->brand << '/' << this->device << ":10" << this->android_id
                << '/' << this->version.incremental << ":user/release-keys";
}

Device::Device(const BaseDevice& basedevice)
    : product(std::move(ByteArray::from(basedevice.product))),
      device(std::move(ByteArray::from(basedevice.device))),
      board(std::move(ByteArray::from(basedevice.board))),
      brand(std::move(ByteArray::from(basedevice.brand))),
      model(std::move(ByteArray::from(basedevice.model))),
      wifi_ssid(std::move(ByteArray::from(basedevice.wifi_ssid))),
      bootloader(std::move(ByteArray::from(basedevice.bootloader))),
      android_id(std::move(ByteArray::from(basedevice.android_id))),
      boot_id(std::move(ByteArray::from(basedevice.boot_id))),
      proc_version(std::move(ByteArray::from(basedevice.proc_version))),
      mac_address(std::move(ByteArray::from(basedevice.mac_address))),
      ip_address(std::move(ByteArray::from(basedevice.ip_address))),
      imei(basedevice.imei),
      guid(std::move(md5(ByteArray::from(imei) + mac_address))) {
    this->version.incremental << basedevice.incremental;
    fingerprint << this->brand << '/' << this->device << ":10" << this->android_id
                << '/' << this->version.incremental << ":user/release-keys";
}

Device::Device(ByteArray product, ByteArray device, ByteArray board, ByteArray brand,
               ByteArray model, ByteArray wifi_ssid, ByteArray bootloader,
               ByteArray android_id, ByteArray boot_id, ByteArray proc_version,
               ByteArray mac_address, ByteArray ip_address, std::string imei,
               ByteArray incremental)
    : product(std::move(product)),
      device(std::move(device)),
      board(std::move(board)),
      brand(std::move(brand)),
      model(std::move(model)),
      wifi_ssid(std::move(wifi_ssid)),
      bootloader(std::move(bootloader)),
      android_id(std::move(android_id)),
      boot_id(std::move(boot_id)),
      proc_version(std::move(proc_version)),
      mac_address(std::move(mac_address)),
      ip_address(std::move(ip_address)),
      imei(std::move(imei)),
      guid(std::move(md5(ByteArray::from(imei) + mac_address))) {
    this->version.incremental = std::move(incremental);
    fingerprint << this->brand << '/' << this->device << ":10" << this->android_id
                << '/' << this->version.incremental << ":user/release-keys";
}
Device::Device(const Device& other)
    : product(other.product),
      device(other.device),
      board(other.board),
      brand(other.brand),
      model(other.model),
      wifi_ssid(other.wifi_ssid),
      bootloader(other.bootloader),
      android_id(other.android_id),
      boot_id(other.boot_id),
      proc_version(other.proc_version),
      mac_address(other.mac_address),
      ip_address(other.ip_address),
      imei(other.imei),
      version(other.version),
      fingerprint(other.fingerprint),
      baseBand(other.baseBand),
      simInfo(other.simInfo),
      osType(other.osType),
      wifi_bssid(other.wifi_bssid),
      imsi(other.imsi),
      apn(other.apn),
      guid(other.guid) {}

std::istream& operator>>(std::istream& stream, Device& info) {
    std::string json_data;
    json_data.assign(std::istreambuf_iterator<char>(stream),
                     std::istreambuf_iterator<char>());
    // 将字符串解析为 JSON 对象
    boost::system::error_code errs;
    boost::json::value        root = boost::json::parse(json_data.c_str(), errs);
    if(errs) {
        throw ParsingException("Error parsing JSON.", ParsingException::JsonError);
    } else {
        try {
            info.product =
                std::move(ByteArray::from<boost::json::value>(root.at("product")));
            info.device =
                std::move(ByteArray::from<boost::json::value>(root.at("device")));
            info.board =
                std::move(ByteArray::from<boost::json::value>(root.at("board")));
            info.model =
                std::move(ByteArray::from<boost::json::value>(root.at("model")));
            info.wifi_ssid =
                std::move(ByteArray::from<boost::json::value>(root.at("wifi_ssid")));
            info.bootloader =
                std::move(ByteArray::from<boost::json::value>(root.at("bootloader")));
            info.android_id =
                std::move(ByteArray::from<boost::json::value>(root.at("android_id")));
            info.boot_id =
                std::move(ByteArray::from<boost::json::value>(root.at("boot_id")));
            info.proc_version =
                std::move(ByteArray::from<boost::json::value>(root.at("proc_version")));
            info.mac_address =
                std::move(ByteArray::from<boost::json::value>(root.at("mac_address")));
            info.ip_address =
                std::move(ByteArray::from<boost::json::value>(root.at("ip_address")));
            info.imei        = root.at("imei").as_string();
            auto incremental = root.at("incremental");
            if(incremental.is_string()) {
                info.version.incremental =
                    std::move(ByteArray::from(std::string(incremental.as_string())));
            } else if(incremental.is_number()) {
                info.version.incremental =
                    std::move(ByteArray::from(std::to_string(incremental.as_uint64())));
            }
        } catch(std::exception) {
            spdlog::warn("try to move");
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Device& info) {
    try {
        /**
            root["product"].as<ByteArray>(),
            root["device"].as<ByteArray>(),
            root["board"].as<ByteArray>(),
            root["brand"].as<ByteArray>(),
            root["model"].as<ByteArray>(),
            root["wifi_ssid"].as<ByteArray>(),
            root["bootloader"].as<ByteArray>(),
            root["android_id"].as<ByteArray>(),
            root["boot_id"].as<ByteArray>(),
            root["proc_version"].as<ByteArray>(),
            root["mac_address"].as<ByteArray>(),
            root["ip_address"].as<ByteArray>(),
           root["imei"].asString(),
            oByteArray(std::to_string(root["incremental"].asUInt())));
         */
        boost::json::value root = {
            { "product", info.product.toString() },
            { "device", info.device.toString() },
            { "board", info.board.toString() },
            { "brand", info.brand.toString() },
            { "model", info.model.toString() },
            { "wifi_ssid", info.wifi_ssid.toString() },
            { "bootloader", info.bootloader.toString() },
            { "android_id", info.android_id.toString() },
            { "boot_id", info.boot_id.toString() },
            { "proc_version", info.proc_version.toString() },
            { "mac_address", info.mac_address.toString() },
            { "imei", info.imei },
            { "incremental", info.version.incremental.to<uint32_t>() },
        };

        // 将 Json::Value 对象转换为字符串
        stream << boost::json::serialize(root);

    } catch(std::exception& except) {
        spdlog::warn("Failed to {}", except.what());
    }
    return stream;
}
}; // namespace Flee
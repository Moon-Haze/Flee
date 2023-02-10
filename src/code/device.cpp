
#include "device.h"
#include "ByteArray.h"
#include "ParsingException.h"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <json/json.h>
#include <json/value.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <string>

namespace Flee {

Device Device::getDevice(const std::string& filename) {
    if(!filename.empty()) {
        std::ifstream file(filename);
        spdlog::info("Device's file name is {}", filename);
        if(!file.is_open()) {
            spdlog::warn("Failed to open file {} in {}", filename, __FILE_NAME__);
        } else {
            std::string json_data((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());
            // 将字符串解析为 JSON 对象
            JSONCPP_STRING          errs;
            Json::Value             root;
            Json::CharReaderBuilder readerBuilder;

            std::unique_ptr<Json::CharReader> const jsonReader(
                readerBuilder.newCharReader());
            auto res =
                jsonReader->parse(json_data.c_str(),
                                  json_data.c_str() + json_data.length(), &root, &errs);
            if(!res) {
                spdlog::warn("Failed to parse JSON data from file {}\n", filename);
            } else {
                /***
                 * "product": "MRS4S",
                 * "device": "HIM188MOE",
                 * "board": "MIRAI-YYDS",
                 * "brand": "OICQX",
                 * "model": "Konata 2020",
                 * "wifi_ssid": "TP-LINK-80fb9b98",
                 * "bootloader": "U-boot",
                 * "android_id": "OICQX.18667125.702",
                 * "boot_id": "48eb7d46-2934-204a-35a4-07ef1daa3111",
                 * "proc_version": "Linux version 4.19.71-10548
                 * (konata@takayama.github.com)", "mac_address":
                 * "00:50:20:4A:35:A4", "ip_address": "10.0.7.239", "imei":
                 * "353301082446845", "incremental": 497692945,
                 */
                return Device(
                    root["product"].as<ByteArray>(), root["device"].as<ByteArray>(),
                    root["board"].as<ByteArray>(), root["brand"].as<ByteArray>(),
                    root["model"].as<ByteArray>(), root["wifi_ssid"].as<ByteArray>(),
                    root["bootloader"].as<ByteArray>(),
                    root["android_id"].as<ByteArray>(), root["boot_id"].as<ByteArray>(),
                    root["proc_version"].as<ByteArray>(),
                    root["mac_address"].as<ByteArray>(),
                    root["ip_address"].as<ByteArray>(), root["imei"].asString(),
                    ByteArray::from(std::to_string(root["incremental"].asUInt())));
            }
        }
    }
    return Device();
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
      imei(std::move(imei)) {
    this->version.incremental = std::move(incremental);
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
      display(other.display),
      fingerprint(other.fingerprint),
      baseBand(other.baseBand),
      simInfo(other.simInfo),
      osType(other.osType),
      wifi_bssid(other.wifi_bssid),
      imsiMd5(other.imsiMd5),
      apn(other.apn),
      guid(other.guid) {}

std::istream& operator>>(std::istream& stream, Device& info) {
    std::string json_data;
    json_data.assign(std::istreambuf_iterator<char>(stream),
                     std::istreambuf_iterator<char>());
    // 将字符串解析为 JSON 对象
    JSONCPP_STRING          errs;
    Json::Value             root;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
    auto                                    res = jsonReader->parse(json_data.c_str(),
                                                                    json_data.c_str() + json_data.length(), &root, &errs);
    if(!res) {
        throw ParsingException("Error parsing JSON.", ParsingException::JsonError);
    } else {
        try {
            info.product      = std::move(root["product"].as<ByteArray>());
            info.device       = std::move(root["device"].as<ByteArray>());
            info.board        = std::move(root["board"].as<ByteArray>());
            info.model        = std::move(root["model"].as<ByteArray>());
            info.wifi_ssid    = std::move(root["wifi_ssid"].as<ByteArray>());
            info.bootloader   = std::move(root["bootloader"].as<ByteArray>());
            info.android_id   = std::move(root["android_id"].as<ByteArray>());
            info.boot_id      = std::move(root["boot_id"].as<ByteArray>());
            info.proc_version = std::move(root["proc_version"].as<ByteArray>());
            info.mac_address  = std::move(root["mac_address"].as<ByteArray>());
            info.ip_address   = std::move(root["ip_address"].as<ByteArray>());
            info.imei         = std::move(root["imei"].asString());

            if(root["incremental"].isString()) {
                info.version.incremental = std::move(
                    ByteArray::from(std::string(root["incremental"].asString())));
            } else if(root["incremental"].isNumeric()) {
                info.version.incremental = std::move(
                    ByteArray::from(std::to_string(root["incremental"].asUInt())));
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
            root["ip_address"].as<ByteArray>(), root["imei"].asString(),
            oByteArray(std::to_string(root["incremental"].asUInt())));
         *
         */
        Json::Value root;
        root["product"]      = info.product.to<std::string>();
        root["device"]       = info.device.to<std::string>();
        root["board"]        = info.board.to<std::string>();
        root["brand"]        = info.brand.to<std::string>();
        root["model"]        = info.model.to<std::string>();
        root["wifi_ssid"]    = info.wifi_ssid.to<std::string>();
        root["bootloader"]   = info.bootloader.to<std::string>();
        root["android_id"]   = info.android_id.to<std::string>();
        root["boot_id"]      = info.boot_id.to<std::string>();
        root["proc_version"] = info.proc_version.to<std::string>();
        root["mac_address"]  = info.mac_address.to<std::string>();
        root["imei"]         = info.imei;
        root["incremental"]  = std::stoi(info.version.incremental.to<std::string>());
        // 创建一个 Json::StyledWriter 对象
        Json::StreamWriterBuilder           writerBuilder;
        std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
        // 将 Json::Value 对象转换为字符串
        jsonWriter->write(root, &stream);
    } catch(std::exception except) {
        spdlog::warn("Failed to {}", except.what());
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Version& version) {
    ByteArray data;
    // stream >> version.incremental >> version.release >> version.codename
    // >> data;
    // data >> version.sdk;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Version& version) {
    // ByteArray data = toByteArray(version.sdk);
    // stream << version.incremental << version.release << version.codename
    //    << data;
    return stream;
}
}; // namespace Flee
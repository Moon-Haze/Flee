#include "QQConfig.h"
#include <string>

namespace Flee {

QQConfig::QQConfig(const std::string& dir) : dir(dir) {}

QQConfig::QQConfig(const QQConfig& other) : dir(other.dir), platform(other.platform) {}

std::string QQConfig::getDir() const { return dir; }

void QQConfig::setDir(const std::string& dir) { this->dir = dir; }

QQConfig::~QQConfig() {}

}; // namespace Flee
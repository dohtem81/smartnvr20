#include "framehandlerconfig.hpp"

using namespace smartnvr20::lib;

namespace smartnvr20::infrastructure {

// ------------------------------------------------------------------
FrameHandlerConfig::FrameHandlerConfig(std::shared_ptr<smartnvr20::lib::FileLocation> _configFileLocation) : iConfiguration(_configFileLocation) {
    
    std::ifstream configFile(_configFileLocation->toString());
    if (!configFile.is_open()) {
        throw std::runtime_error("Can't open file: " + _configFileLocation->toString());
    }

    nlohmann::json j;
    configFile >> j;

    if (j.contains("commbus")) {
        host = j["commbus"]["host"];
        port = j["commbus"].contains("port") ? j["commbus"]["port"].get<int>() : 6379;
        dbPassword = j["commbus"].contains("pswd") ? j["commbus"]["pswd"] : "";
    } else {
        throw std::runtime_error("Missing 'commbus' section in config file");
    }
}


// ------------------------------------------------------------------
FrameHandlerConfig::FrameHandlerConfig(const std::string& _host, int _port = 6379, const std::string& _dbPassword = "")
    : iConfiguration(), host(_host), port(_port), dbPassword(_dbPassword) {
}


// ------------------------------------------------------------------

} // namespace smartnvr20::infrastructure
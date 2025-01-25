#ifndef FRAMEHANDLERCONFIG_HPP
#define FRAMEHANDLERCONFIG_HPP

#include "../lib/iConfiguration.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <memory>

using namespace smartnvr20::lib;

namespace smartnvr20::infrastructure {

class FrameHandlerConfig : public iConfiguration {
public:
    FrameHandlerConfig(std::shared_ptr<smartnvr20::lib::FileLocation> _configFileLocation);

    std::string getHost() { return host; }
    int getPort() { return port; }
    std::string getPassword() { return (dbPassword.empty() ? "" : dbPassword); }
private:
    std::string host;
    int port;
    std::string dbPassword;
};

} // namespace smartnvr20::infrastructure

#endif // FRAMEHANDLERCONFIG_HPP
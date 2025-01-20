#include "cameraConfig.hpp"

namespace smartnvr20::infrastructure
{

    CameraConfig::CameraConfig(std::shared_ptr<lib::FileLocation> _fileLocation) : fileLocation(_fileLocation)
    {
        std::ifstream f("config.json");
        nlohmann::json data;
        f >> data;

        // set where the logfiles will be written to
        url = data["connectionstring"];
        name = data["name"];
    }

    std::string CameraConfig::toString() const
    {
        std::stringstream ss;
        ss << "Name: " << name;
        ss << " URL: " << url;
        ss << std::endl;
        return ss.str();
    }    

} // namespace smartnvr20
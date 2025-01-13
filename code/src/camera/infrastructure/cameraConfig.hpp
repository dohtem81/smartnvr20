// File: cameraConfig.hpp

#ifndef CAMERA_CONFIG_HPP
#define CAMERA_CONFIG_HPP

#include <memory>
#include "../../lib/FileLocation.hpp"
#include "../../lib/iToString.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace smartnvr20::infrastructure
{
    struct CameraConfig : public lib::iToString
    {   
        public:
        CameraConfig(std::shared_ptr<lib::FileLocation>);

        // getters
        std::shared_ptr<smartnvr20::lib::FileLocation> getFileLocation() { return fileLocation; }
        std::string getURL() { return url; }
        std::string getName() { return name; }

        std::string toString() const override;

        private:
        std::shared_ptr<lib::FileLocation> fileLocation;
        std::string url;
        std::string name;
    };

} // namespace smartnvr20::infrastructure
#endif // CAMERA_CONFIG_HPP
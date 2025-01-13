#include "cameraDevice.hpp"

namespace smartnvr20::application {

std::shared_ptr<CameraDevice> CameraDeviceFactory()
{
    CameraDevice* _cameraDevice = new CameraDevice();
    return std::shared_ptr<CameraDevice>(_cameraDevice);
}

CameraDevice::CameraDevice(std::shared_ptr<lib::FileLocation> _configFileLocation)
{
    config = std::make_shared<infrastructure::CameraConfig>(_configFileLocation);

    name = config->getName();
    streamUrl = config->getURL();
}

void *Camera::mainLoop()
{

}

} // namespace smartnvr20::application
#ifndef CAMERADEVICE_HPP
#define CAMERADEVICE_HPP

#include <memory>
#include <opencv2/videoio.hpp>
#include <spdlog/spdlog.h>
#include "../../lib/FileLocation.hpp"
#include "../infrastructure/cameraConfig.hpp"

namespace smartnvr20::application {

class CameraDevice {
public:
    friend std::shared_ptr<CameraDevice> CameraDeviceFactory(std::shared_ptr<lib::FileLocation>);
    void attachLogger(spdlog::logger *);

    pthread_t camera_thread;

private:
    CameraDevice(std::shared_ptr<lib::FileLocation>);
    static void *cameraMainLoop(void *);
    void *mainLoop();
    std::shared_ptr<spdlog::logger> logger;
    bool active;    

    std::shared_ptr<smartnvr20::infrastructure::CameraConfig> config;
    std::string streamUrl;
    std::string name;
    std::shared_ptr<cv::VideoCapture> cap;
};

std::shared_ptr<CameraDevice> CameraDeviceFactory(std::shared_ptr<lib::FileLocation>);

//} // namespace application
} // namespace smartnvr20

#endif // CAMERADEVICE_HPP
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>
#include <opencv2/videoio.hpp>
#include <spdlog/spdlog.h>
#include "../../lib/FileLocation.hpp"
#include "../infrastructure/cameraConfig.hpp"

namespace smartnvr20 {
namespace application {

class Camera {
public:
    friend std::shared_ptr<Camera> CameraFactory(std::shared_ptr<lib::FileLocation>);

    void run();
    pthread_t camera_thread;

private:
    Camera(std::shared_ptr<lib::FileLocation> _configFileLocation);
    static void *cameraMainLoop(void *);
    void *mainLoop();
    std::shared_ptr<spdlog::logger> logger;
    bool active;
    float f_measure_fps;
    int i_measure_fps() { return int(f_measure_fps); };
    std::shared_ptr<cv::VideoCapture> cap;
    std::shared_ptr<smartnvr20::infrastructure::CameraConfig> config;
};

// Forward declaration of the friend method
std::shared_ptr<Camera> CameraFactory(std::shared_ptr<lib::FileLocation>);

} // namespace application
} // namespace smartnvr20

#endif // CAMERA_HPP
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <thread>

namespace smartnvr20 {

class Camera {
public:
    friend std::shared_ptr<Camera> CameraFactory();
    static bool initialized;

    void run();
    pthread_t camera_thread;

private:
    Camera();
    static void *cameraMainLoop(void *);
    void *mainLoop();
    std::shared_ptr<spdlog::logger> logger;
    bool active;
};

// forward definition of the freind method
std::shared_ptr<Camera> CameraFactory();

} // namespace smartnvr20

#endif // CAMERA_HPP
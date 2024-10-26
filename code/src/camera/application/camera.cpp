#include "camera.hpp"

namespace smartnvr20 {

void Camera::run()
{
    pthread_create(&camera_thread, NULL, Camera::cameraMainLoop, this);  
    return;
}

void *Camera::cameraMainLoop(void *context)
{
    return static_cast<Camera*>(context)->mainLoop();
}

void *Camera::mainLoop()
{
    spdlog::info("camera is active and running");
    while(true)
    {
        spdlog::info("camera tick");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}

std::shared_ptr<Camera> CameraFactory()
{
    // if (Camera::initialized)
    //     return nullptr;
    
    Camera* _camera = new Camera();
    //Camera::initialized = true;
    std::shared_ptr<Camera> cameraUPtr(_camera);

    return cameraUPtr;    
}

Camera::Camera()
{
    logger = spdlog::daily_logger_mt("daily_logger", "./", 0, 00);
    spdlog::info("Camera object created");

}

} // namespace smartnvr20

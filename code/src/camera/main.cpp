#include "application/camera.hpp"

using namespace smartnvr20;

int main()
{
    std::shared_ptr<Camera> camera = CameraFactory();
    camera->run();
    pthread_join(camera->camera_thread, NULL);    

    return 0;
}
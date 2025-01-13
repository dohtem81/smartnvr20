#include <iostream>
#include "../camera/application/camera.hpp"
#include "../lib/FileLocation.hpp"

using namespace smartnvr20;

int main()
{
    const char* configPath = std::getenv("CONFIG_PATH");
    if (configPath == nullptr) {
        std::cerr << "CONFIG_PATH environment variable is not set. Using default path." << std::endl;
        return 1;
    }

    
    std::shared_ptr<lib::FileLocation> configFileLocation = std::make_shared<lib::FileLocation>(configPath, "camera_config_test.json");    
    //std::shared_ptr<application::Camera> camera = application::CameraFactory(configFileLocation);
    //camera->run();
    //pthread_join(camera->camera_thread, NULL);    

    return 0;
}
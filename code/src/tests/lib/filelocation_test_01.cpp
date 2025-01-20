#include "../../lib/FileLocation.hpp"
#include <memory>
#include <iostream>

int main(void)
{
    std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation = std::make_shared<smartnvr20::lib::FileLocation>("./config/", "cameraDevice.json");
    std::cout << fileLocation->toString() << std::endl;

    return 0;
}
#include <iostream>
#include "domain/framhandler.hpp"

using namespace smartnvr20;

int main()
{
    std::shared_ptr<commbus::domain::FrameHandler> frameHandler = commbus::domain::FrameHandlerFactory();
    if (frameHandler == nullptr)
    {
        std::cout << "FrameHandlerFactory returned nullptr" << std::endl;
    }
    else
    {
        std::cout << frameHandler->toString() << std::endl;
    }

    frameHandler = commbus::domain::FrameHandlerFactory();
    if (frameHandler == nullptr)
    {
        std::cout << "FrameHandlerFactory returned nullptr" << std::endl;
    }
    else
    {
        std::cout << frameHandler->toString() << std::endl;
    }    
    return 0;
}
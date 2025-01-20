#include "camera.hpp"

using namespace smartnvr20::application;
using namespace smartnvr20;

std::shared_ptr<Camera> CameraFactory(std::shared_ptr<lib::FileLocation> _configFileLocation)
{
    return std::make_shared<Camera>(_configFileLocation);
}

Camera::Camera(std::shared_ptr<lib::FileLocation> _configFileLocation)
{
    config = std::make_shared<infrastructure::CameraConfig>(_configFileLocation);
}

void *Camera::mainLoop()
{
    spdlog::info("camera mainloop entered");

    int retryConncetion = 0;
    cap = std::make_shared<cv::VideoCapture>();

    // Variables for FPS calculation
    int frameCount = 0;
    double fps = 0.0;
    double startTime = cv::getTickCount();

    // Initialize Redis connection
    redisContext* redisContext = redisConnect("127.0.0.1", 6379);
    if (redisContext == nullptr || redisContext->err) {
        if (redisContext) {
            spdlog::error("Redis connection error: " + std::string(redisContext->errstr));
            redisFree(redisContext);
        } else {
            spdlog::error("Can't allocate Redis context");
        }
        return nullptr;
    }

    while(active)
    {
        // if cap is not opened, try to open it
        if (!cap->isOpened())
        {
            retryConncetion++;
            cap->open(config->getURL());
            if (cap->isOpened())
            {
                //this->features = CameraFeatures::CameraFeaturesFactory(cap);
                //spdlog::info(conectionString + " [SUCCESS]" + " >>> features " + CameraFeatures::to_string(features));
                spdlog::info(config->getURL() + " [SUCCESS]");
                // reset retry counter for the future
                retryConncetion = 0;
            }
            else
            {
                if (retryConncetion > 3)
                {
                    spdlog::error(config->getURL() + " [FAILED]"); 
                    break;
                }
            }
        }
        else // this is the case when cap is opened
        {
            conectionEstablished = true;
            if (cap->read(currentFrame))
            {
                //Frame frameToAdd;
                //currentFrame.copyTo(frameToAdd);
                collectedFrames++;
                //frames_ptr->addFrame(std::make_shared<Frame>(frameToAdd));

                // Serialize the frame
                std::vector<uchar> buf;
                cv::imencode(".jpg", currentFrame, buf);
                std::string encodedFrame(buf.begin(), buf.end());

                // Add the frame to the Redis queue with expiration
                redisReply* reply = (redisReply*)redisCommand(redisContext, "RPUSH my_queue %b", encodedFrame.data(), encodedFrame.size());
                if (reply == nullptr) {
                    spdlog::error("Redis RPUSH error: " + std::string(redisContext->errstr));
                } else {
                    freeReplyObject(reply);
                    // Set expiration time for the queue (e.g., 10 seconds)
                    reply = (redisReply*)redisCommand(redisContext, "EXPIRE my_queue 10");
                    if (reply == nullptr) {
                        spdlog::error("Redis EXPIRE error: " + std::string(redisContext->errstr));
                    } else {
                        freeReplyObject(reply);
                    }
                }

                // Increment frame count
                frameCount++;

                // Calculate elapsed time
                double currentTime = cv::getTickCount();
                double elapsedTime = (currentTime - startTime) / cv::getTickFrequency();

                // Update FPS every second
                if (elapsedTime >= 1.0)
                {
                    fps = frameCount / elapsedTime;
                    spdlog::info("FPS: " + std::to_string(fps));

                    // Reset frame count and start time
                    frameCount = 0;
                    startTime = currentTime;
                }
            }
        }
    }

    cap->release();
    redisFree(redisContext); // Clean up Redis connection
    spdlog::info("Stopping >>" + config->getURL() + " [SUCCESS]");
    return 0;
}

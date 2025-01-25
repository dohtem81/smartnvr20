#include "busclient.hpp"
#include <iostream>

namespace smartnvr20::infrastructure::busclient {

// ------------------------------------------------------------------
std::shared_ptr<BusClient> BusClientFactory(std::string host, int port, std::string password)
{
    std::shared_ptr<BusClient> busClientPtr = std::shared_ptr<BusClient>(new BusClient(host, port));
    if (busClientPtr->rContext == nullptr)
    {
        return nullptr;
    }

    busClientPtr->authRequired = true;

    // if password is not empty authorize
    if (busClientPtr->authRequired && !password.empty())
    {
        busClientPtr->status = busClientPtr->Authorize(password) == BusStatus::OK ? BusStatus::OK : BusStatus::AUTH_ERROR;
    }
    
    return busClientPtr;
}

// ------------------------------------------------------------------
BusClient::BusClient(std::string host, int port)
{
    rContext = GetBusContext(host, port);
    rContext == nullptr ? status = BusStatus::ERROR : status = BusStatus::OK;
}


// ------------------------------------------------------------------
std::shared_ptr<redisContext> BusClient::GetBusContext(std::string host, int port)
{
    redisContext* rawContext = redisConnect(host.c_str(), port);
    if (rawContext == nullptr || rawContext->err)
    {
        if (rawContext->err)
            redisFree(rawContext);
        return nullptr;
    }

    return std::shared_ptr<redisContext>(rawContext);
}


// ------------------------------------------------------------------
BusStatus BusClient::Authorize(std::string _password)
{
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "AUTH %s", _password.c_str());
    if (reply == nullptr)
    {
        //throw BusClientException("Failed to authenticate to redis server");
        return BusStatus::AUTH_ERROR;
    }

    if (reply->type == REDIS_REPLY_ERROR)
    {
        std::string replyStr = "Failed to authenticate to redis server: ";
        replyStr += reply->str;
        freeReplyObject(reply);
        return BusStatus::AUTH_ERROR;
    }

    freeReplyObject(reply);
    return BusStatus::OK;
}


// ------------------------------------------------------------------
std::string BusClient::toString() const
{
    std::string outStr = "";

    if (rContext == nullptr)
    {
        outStr = "Redis conection not initialized\n";
    }
    else
    {
        outStr = "Redis host: " + std::string(rContext->tcp.host) + 
            " port: " + std::to_string(rContext->tcp.port) + 
            " AUTH: " + (authRequired ? "YES" : "NO") +
            " STATUS: " + to_string(status) +
            "\n";
    }

    return outStr;
}

} // namespace smartnvr20::infrastructure::redisclient
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
    busClientPtr->status = busClientPtr->Authorize(password) == BusStatus::OK ? BusStatus::OK : BusStatus::AUTH_ERROR;
    
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


// ------------------------------------------------------------------
bool BusClient::SetExpiration(const std::string& key, int seconds)
{
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "EXPIRE %s %d", key.c_str(), seconds);
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);

    return true;
}


// ------------------------------------------------------------------
int BusClient::GetExpiration(const std::string& key)
{
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "TTL %s", key.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) freeReplyObject(reply);
        return -1;
    }

    int ttl = reply->integer;
    freeReplyObject(reply);

    return ttl;
}


// ------------------------------------------------------------------
int BusClient::GetQueueLength(const std::string& key)
{
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "LLEN %s", key.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) freeReplyObject(reply);
        return -1;
    }

    int len = reply->integer;
    freeReplyObject(reply);

    return len;
}


// ------------------------------------------------------------------
int BusClient::GetExpiringQueueLength(const std::string& queueKey) {
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "LRANGE %s 0 -1", queueKey.c_str());
    if (!reply) return 0;
    
    CleanupExpiredKeys(queueKey);
    return GetQueueLength(queueKey);
    // int validKeys = 0;
    // for (size_t i = 0; i < reply->elements; i++) {
    //     std::string itemKey = reply->element[i]->str;
    //     if (KeyExists(itemKey)) {
    //         validKeys++;
    //     }
    // }
    
    // freeReplyObject(reply);
    // return validKeys;
}


// ------------------------------------------------------------------
bool BusClient::KeyExists(const std::string& key) {
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "EXISTS %s", key.c_str());
    if (!reply) return false;
    
    bool exists = (reply->integer == 1);
    freeReplyObject(reply);
    return exists;
}


// ------------------------------------------------------------------
bool BusClient::CleanupExpiredKeys(const std::string& queueKey) {
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "LRANGE %s 0 -1", queueKey.c_str());
    if (!reply) return false;

    // Start transaction
    redisCommand(rContext.get(), "MULTI");

    // Remove expired items
    for (size_t i = 0; i < reply->elements; i++) {
        std::string itemKey = reply->element[i]->str;
        if (IsKeyExpired(itemKey)) {
            redisCommand(rContext.get(), "LREM %s 0 %s", queueKey.c_str(), itemKey.c_str());
        }
        else break;
    }

    // Execute transaction
    redisCommand(rContext.get(), "EXEC");
    freeReplyObject(reply);
    return true;
}


// ------------------------------------------------------------------
bool BusClient::IsKeyExpired(const std::string& key) {
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "EXISTS %s", key.c_str());
    if (!reply) return true;
    
    bool expired = (reply->integer == 0);
    freeReplyObject(reply);
    return expired;
}

} // namespace smartnvr20::infrastructure::redisclient
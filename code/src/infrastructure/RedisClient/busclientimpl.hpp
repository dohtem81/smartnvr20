#ifndef BUSCLIENT_IMPL_HPP
#define BUSCLIENT_IMPL_HPP

namespace smartnvr20::infrastructure::busclient {

template <typename T>
bool BusClient::StoreInRedis(const std::string& key, const T& value)
{
    std::ostringstream oss;
    oss << value;
    std::string valueStr = oss.str();

    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "SET %s %s", key.c_str(), valueStr.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);
    return true;
}

template <typename T>
bool BusClient::AddToRedisQueue(const std::string& key, const T& value)
{
    std::ostringstream oss;
    oss << value;
    std::string valueStr = oss.str();

    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "LPUSH %s %s", key.c_str(), valueStr.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) freeReplyObject(reply);
        return false;
    }
    freeReplyObject(reply);
    return true;
}

template <typename T>
bool BusClient::GetFromRedis(const std::string& key, T& value)
{
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "GET %s", key.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) 
            freeReplyObject(reply);
        return false;
    }

    if (reply->str != nullptr)
    {
        std::istringstream iss(reply->str);
        iss >> value;
        freeReplyObject(reply);
        return true;
    }
    freeReplyObject(reply);
    return false;
}

template <typename T>
bool BusClient::GetFromRedisQueue(const std::string& key, T& value)
{
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "RPOP %s", key.c_str());
    if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
    {
        if (reply) freeReplyObject(reply);
        return false;
    }

    if (reply->str == nullptr)
    {
        freeReplyObject(reply);
        return false;
    }

    std::istringstream iss(reply->str);
    iss >> value;
    freeReplyObject(reply);
    return true;
}

template <typename T>
bool BusClient::AddToRedisQueueWithExpiry(const std::string& queueKey, const T& value, int ttlSeconds)
{
    // Generate unique item key
    std::string itemKey = queueKey + ":item:" + std::to_string(time(nullptr));
    
    // Convert value to string
    std::ostringstream oss;
    oss << value;
    std::string valueStr = oss.str();

    // MULTI - Start transaction
    redisReply* reply = (redisReply*)redisCommand(rContext.get(), "MULTI");
    if (!reply) return false;
    freeReplyObject(reply);

    // SET item with TTL
    reply = (redisReply*)redisCommand(rContext.get(), "SETEX %s %d %s", 
        itemKey.c_str(), ttlSeconds, valueStr.c_str());
    if (!reply) return false;
    freeReplyObject(reply);

    // LPUSH reference to list
    reply = (redisReply*)redisCommand(rContext.get(), "LPUSH %s %s", 
        queueKey.c_str(), itemKey.c_str());
    if (!reply) return false;
    freeReplyObject(reply);

    // EXEC - Execute transaction
    reply = (redisReply*)redisCommand(rContext.get(), "EXEC");
    if (!reply) return false;
    freeReplyObject(reply);

    return true;
}

} // namespace smartnvr20::infrastructure::busclient

#endif // BUSCLIENT_IMPL_HPP
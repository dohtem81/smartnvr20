#ifndef BUSCLIENT_HPP
#define BUSCLIENT_HPP

#include <hiredis/hiredis.h>
#include "../../lib/iToString.hpp"
#include <memory>
#include "../framehandlerconfig.hpp"
#include "busclient_exceptions.hpp"

namespace smartnvr20::infrastructure::busclient {

enum class BusStatus
{
    OK,
    ERROR,
    AUTH_ERROR
};

inline std::string to_string(BusStatus status)
{
    switch (status)
    {
    case BusStatus::OK:
        return "OK";
    case BusStatus::ERROR:
        return "ERROR";
    case BusStatus::AUTH_ERROR:
        return "AUTH_ERROR";
    default:
        return "UNKNOWN";
    }
}

class BusClient : public smartnvr20::lib::iToString
{
public:
    std::string toString() const;
    friend std::shared_ptr<BusClient> BusClientFactory(std::string host, int port, std::string password);
    std::shared_ptr<redisContext> GetBusContext(std::string, int);
    template <typename T>
    bool StoreInRedis(const std::string& key, const T& value);
    template <typename T>
    bool AddToRedisQueue(const std::string& key, const T& value);
    bool SetExpiration(const std::string& key, int seconds);
    template <typename T>
    bool AddToRedisQueueWithExpiry(const std::string& queueKey, const T& value, int ttlSeconds);   
    template <typename T>
    bool GetFromRedis(const std::string& key, T& value);
    template <typename T>
    bool GetFromRedisQueue(const std::string& key, T& value);
    int GetExpiration(const std::string& key);
    int GetQueueLength(const std::string& key);
    int GetExpiringQueueLength(const std::string& key);
    bool KeyExists(const std::string& key);
    bool CleanupExpiredKeys(const std::string& queueKey);
    bool IsKeyExpired(const std::string& key);

private:
    BusStatus status;
    std::shared_ptr<redisContext> rContext;
    BusClient(std::string, int);
    BusStatus Authorize(std::string);
    bool authRequired;
};

std::shared_ptr<BusClient> BusClientFactory(std::string host, int port = 6379, std::string password = "");
} // namespace smartnvr20::infrastructure::redisclient

#include "busclientimpl.hpp"

#endif // BUSCLIENT_HPP
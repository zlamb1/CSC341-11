#pragma once

#include <memory>
#include <stdint.h>
#include <string>

class INetworkServer {
    public:
        INetworkServer() {}
        virtual ~INetworkServer() = default;

        virtual void listen(std::string hostAddress, uint16_t port) = 0;
};

using INetworkServerRef = std::shared_ptr<INetworkServer>;
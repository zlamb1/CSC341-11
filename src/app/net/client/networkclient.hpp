#pragma once

#include <functional>
#include <memory>

#include "net/packet/base.hpp"
#include "net/packet/dest.hpp"

using ConnectHandler    = std::function<void()>;
using DisconnectHandler = std::function<void()>;

class INetworkClient {
    public:
        virtual ~INetworkClient() = default;

        virtual void connect(std::string hostAddress, uint16_t port) = 0;
        virtual void write(BasePacketRef basePacket)                 = 0;

        virtual void addPacketHandler(PacketHandlerRef packetHandler);
        virtual bool removePacketHandler(PacketHandlerRef packetHandler);

        virtual void handlePacket(BasePacketRef packet);

        virtual void setConnectHandler(ConnectHandler connectHandler);
        virtual void setDisconnectHandler(DisconnectHandler disconnectHandler);

    protected:
        PacketHandlerRef m_PacketHandlers;

        ConnectHandler m_ConnectHandler;
        DisconnectHandler m_DisconnectHandler;
};

using INetworkClientRef = std::shared_ptr<INetworkClient>;
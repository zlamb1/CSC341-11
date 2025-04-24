#pragma once

#include <memory>

#include "net/packet/base.hpp"
#include "net/packet/dest.hpp"

class INetworkClient {
    public:
        virtual ~INetworkClient() = default;

        virtual void connect(std::string hostAddress, uint16_t port) = 0;
        virtual void write(BasePacketRef basePacket)                 = 0;

        virtual void addPacketHandler(PacketHandlerRef packetHandler);
        virtual bool removePacketHandler(PacketHandlerRef packetHandler);

        virtual void handlePacket(BasePacketRef packet);

    protected:
        PacketHandlerRef m_PacketHandlers;
};

using INetworkClientRef = std::shared_ptr<INetworkClient>;
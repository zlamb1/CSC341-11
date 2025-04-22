#pragma once

#include <memory>

#include "net/packet/dest.hpp"
#include "packet/base.hpp"

class INetworkService {
    public:
        virtual void
        addPacketDestination(PacketDestinationRef packetDestination);
        virtual bool
        removePacketDestination(PacketDestinationRef packetDestination);

        virtual void writePacket(BasePacketRef packet) = 0;

    protected:
        PacketDestinationRef m_DestinationChain;

        virtual void onReadPacket(BasePacketRef packet, UserRef sender);
};

using INetworkServiceRef = std::shared_ptr<INetworkService>;
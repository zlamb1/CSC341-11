#include "networkservice.hpp"
#include "net/packet/dest.hpp"

void INetworkService::addPacketDestination(
    PacketDestinationRef packetDestination) {
    if (m_DestinationChain) {
        packetDestination->setNext(m_DestinationChain);
        m_DestinationChain = packetDestination;
    } else {
        m_DestinationChain = packetDestination;
    }
}
bool INetworkService::removePacketDestination(
    PacketDestinationRef packetDestination) {
    PacketDestinationRef prevPacketDestination;
    auto curPacketDestination = m_DestinationChain;
    while (curPacketDestination) {
        if (curPacketDestination == packetDestination) {
            if (prevPacketDestination) {
                prevPacketDestination->setNext(packetDestination);
                return true;
            } else {
                packetDestination->setNext(curPacketDestination->next());
                m_DestinationChain = packetDestination;
                return true;
            }
        }
        prevPacketDestination = curPacketDestination;
        curPacketDestination  = curPacketDestination->next();
    }
    return false;
}

void INetworkService::onReadPacket(BasePacketRef packet, UserRef sender) {
    PacketRequest packetRequest{packet, sender};
    auto packetDestination = m_DestinationChain;
    while (!packetRequest.accepted() && packetDestination) {
        packetDestination->handlePacket(&packetRequest);
        packetDestination = packetDestination->next();
    }
}
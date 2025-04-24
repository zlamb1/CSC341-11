#include "networkclient.hpp"
#include "net/packet/dest.hpp"

void INetworkClient::addPacketHandler(PacketHandlerRef packetHandler) {
    if (m_PacketHandlers) {
        packetHandler->setNext(m_PacketHandlers);
        m_PacketHandlers = packetHandler;
    } else {
        m_PacketHandlers = packetHandler;
    }
}

bool INetworkClient::removePacketHandler(PacketHandlerRef packetHandler) {
    PacketHandlerRef prevPacketHandler, curPacketHandler = m_PacketHandlers;
    while (curPacketHandler) {
        if (curPacketHandler == packetHandler) {
            if (prevPacketHandler) {
                prevPacketHandler->setNext(curPacketHandler->next());
            } else {
                m_PacketHandlers = curPacketHandler->next();
            }
            return true;
        }
        prevPacketHandler = curPacketHandler;
        curPacketHandler  = curPacketHandler->next();
    }

    return false;
}

void INetworkClient::handlePacket(BasePacketRef packet) {
    PacketRequest packetRequest{packet};
    auto packetHandler = m_PacketHandlers;
    while (!packetRequest.accepted() && packetHandler) {
        packetHandler->handlePacket(&packetRequest);
        packetHandler = packetHandler->next();
    }
}

void INetworkClient::setDisconnectHandler(DisconnectHandler disconnectHandler) {
    m_DisconnectHandler = disconnectHandler;
}
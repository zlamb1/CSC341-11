#include <memory>

#include "client.hpp"
#include "net/packet/base.hpp"
#include "net/packet/qt/worker.hpp"
#include "net/packet/user.hpp"

ClientConnection::ClientConnection(qintptr socketDescriptor) {
    m_PacketWorker = new QtThreadedPacketWorker(socketDescriptor);

    QObject::connect(m_PacketWorker, &QtThreadedPacketWorker::disconnected,
                     this, &ClientConnection::disconnected);

    QObject::connect(m_PacketWorker, &QtThreadedPacketWorker::packetRead, this,
                     &ClientConnection::receivePacket);
}

ClientConnection::~ClientConnection() {
    delete m_PacketWorker;
}

void ClientConnection::writePacket(BasePacketRef basePacket) {
    m_PacketWorker->writePacket(basePacket);
}

const std::string &ClientConnection::name() const {
    return m_Name;
}

void ClientConnection::setName(std::string name) {
    m_Name      = name;
    m_Connected = true;
}

bool ClientConnection::isConnected() const {
    return m_Connected;
}

void ClientConnection::receivePacket(BasePacketRef basePacket) {
    // ignore received packets until client establishes identity
    if (m_Connected) {
        emit packetRead(this, basePacket);
    } else if (basePacket->packetType() == PacketType::UserConnect) {
        auto packet = std::dynamic_pointer_cast<UserConnectPacket>(basePacket);
        emit connected(packet->name());
    }
}
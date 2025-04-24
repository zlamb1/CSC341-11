#include <QHostAddress>
#include <qglobal.h>
#include <qobject.h>
#include <qtcpsocket.h>

#include "net/packet/base.hpp"
#include "net/packet/qt/worker.hpp"
#include "net/packet/user.hpp"
#include "networkclient.hpp"
#include "service/userservice.hpp"

QtNetworkClient::QtNetworkClient(std::string requestedName,
                                 IUserServiceRef userService)
    : m_RequestedName(requestedName), m_UserService(userService) {
    auto socket    = new QTcpSocket;
    m_PacketWorker = new QtThreadedPacketWorker(socket);

    QObject::connect(
        m_PacketWorker, &QtThreadedPacketWorker::connected, [this]() {
            auto packet = CreatePacketRef<UserConnectPacket>(m_RequestedName);
            m_PacketWorker->writePacket(packet);
        });

    QObject::connect(m_PacketWorker, &QtThreadedPacketWorker::packetRead, this,
                     &QtNetworkClient::packetRead);
}

QtNetworkClient::~QtNetworkClient() {
    delete m_PacketWorker;
}

void QtNetworkClient::connect(std::string hostAddress, uint16_t port) {
    m_PacketWorker->connect(hostAddress, port);
}

void QtNetworkClient::write(BasePacketRef basePacket) {
    m_PacketWorker->writePacket(basePacket);
}

void QtNetworkClient::packetRead(BasePacketRef basePacket) {
    if (basePacket) {
        handlePacket(basePacket);
    }
}
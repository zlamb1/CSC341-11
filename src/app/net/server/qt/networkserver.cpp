#include "networkserver.hpp"
#include "net/packet/base.hpp"
#include "net/packet/msg.hpp"
#include "net/packet/qt/client.hpp"
#include "net/packet/user.hpp"
#include "service/userservice.hpp"
#include <memory>

QtNetworkServer::QtNetworkServer(IUserServiceRef userService)
    : m_UserService(userService) {}

QtNetworkServer::~QtNetworkServer() {
    for (auto clientConnection : m_ClientConnections)
        delete clientConnection;
}

void QtNetworkServer::listen(std::string hostAddress, uint16_t port) {
    QHostAddress qHostAddress;
    qHostAddress.setAddress(QString::fromStdString(hostAddress));
    QTcpServer::listen(qHostAddress, port);
}

void QtNetworkServer::broadcastPacket(BasePacketRef basePacket) {
    for (auto clientConnection : m_ClientConnections) {
        clientConnection->writePacket(basePacket);
    }
}

void QtNetworkServer::incomingConnection(qintptr socketDescriptor) {
    auto clientConnection = new ClientConnection(socketDescriptor);

    QObject::connect(
        clientConnection, &ClientConnection::connected,
        [this, clientConnection](auto name) {
            // notify all clients of new client
            auto connectPacket = CreatePacketRef<UserConnectPacket>(name);
            for (auto conn : m_ClientConnections) {
                if (conn != clientConnection && conn->isConnected()) {
                    conn->writePacket(connectPacket);
                }
            }

            // connect client
            clientConnection->setName(name);

            // notify new client of all clients
            for (auto conn : m_ClientConnections) {
                if (conn->isConnected()) {
                    auto connectPacket = CreatePacketRef<UserConnectPacket>(
                        conn->name(), conn == clientConnection);
                    clientConnection->writePacket(connectPacket);
                }
            }
        });

    /* clean up disconnected connections */
    QObject::connect(clientConnection, &ClientConnection::disconnected,
                     [this, clientConnection]() {
                         m_ClientConnections.removeOne(clientConnection);
                         if (clientConnection->isConnected()) {
                             auto name = clientConnection->name();
                             auto disconnectPacket =
                                 CreatePacketRef<UserDisconnectPacket>(name);
                             broadcastPacket(disconnectPacket);
                         }
                         clientConnection->deleteLater();
                     });

    QObject::connect(clientConnection, &ClientConnection::packetRead, this,
                     &QtNetworkServer::packetRead);

    m_ClientConnections.append(clientConnection);
}

void QtNetworkServer::packetRead(ClientConnection *conn,
                                 BasePacketRef basePacket) {
    if (!conn->isConnected())
        return;

    switch (basePacket->packetType()) {
    case PacketType::MessageSend: {
        auto messageSendPacket =
            std::dynamic_pointer_cast<MessageSendPacket>(basePacket);
        auto packet = CreatePacketRef<MessageReceivePacket>(
            messageSendPacket->text(), conn->name());
        broadcastPacket(packet);
        break;
    }
    default:
        break;
    }
}
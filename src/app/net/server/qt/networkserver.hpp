#pragma once

#include <QList>
#include <QTcpServer>
#include <QThread>

#include <stdint.h>
#include <string>

#include "net/packet/base.hpp"
#include "net/packet/qt/client.hpp"
#include "net/server/networkserver.hpp"
#include "service/userservice.hpp"

class QtNetworkServer : public QTcpServer, public INetworkServer {
        Q_OBJECT
    public:
        QtNetworkServer(IUserServiceRef userService);
        virtual ~QtNetworkServer();

        virtual void listen(std::string hostAddress, uint16_t port) override;

    protected:
        IUserServiceRef m_UserService;

        QList<ClientConnection *> m_ClientConnections;

        void incomingConnection(qintptr socketDescriptor) override;
        void broadcastPacket(BasePacketRef basePacket);

        void packetRead(ClientConnection *conn, BasePacketRef basePacket);
};
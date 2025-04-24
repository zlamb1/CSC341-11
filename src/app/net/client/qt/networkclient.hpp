#pragma once

#include <QTcpSocket>

#include "net/client/networkclient.hpp"
#include "net/packet/base.hpp"
#include "net/packet/qt/worker.hpp"
#include "service/userservice.hpp"

class QtNetworkClient : public QObject, public INetworkClient {
        Q_OBJECT
    public:
        QtNetworkClient(std::string requestedName, IUserServiceRef userService);
        ~QtNetworkClient();

        virtual void connect(std::string hostAddress, uint16_t port) override;
        virtual void write(BasePacketRef basePacket) override;

    protected:
        std::string m_RequestedName;
        IUserServiceRef m_UserService;

        QtThreadedPacketWorker *m_PacketWorker;

    protected slots:
        void packetRead(BasePacketRef basePacket);
};
#pragma once

#include <QObject>

#include "net/packet/base.hpp"
#include "net/packet/qt/worker.hpp"

class ClientConnection : public QObject {
        Q_OBJECT
    public:
        ClientConnection(qintptr socketDescriptor);
        ~ClientConnection();

        void writePacket(BasePacketRef basePacket);

        const std::string &name() const;
        void setName(std::string);

        bool isConnected() const;

    signals:
        void connected(std::string name);
        void disconnected();

        void packetRead(ClientConnection *conn, BasePacketRef basePacket);

    protected:
        QtThreadedPacketWorker *m_PacketWorker;

        std::string m_Name;

        bool m_Connected = false;

    protected slots:
        void receivePacket(BasePacketRef basePacket);
};
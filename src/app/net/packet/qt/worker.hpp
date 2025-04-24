#pragma once

#include <QTcpSocket>
#include <QThread>
#include <QtCore>

#include "net/packet/base.hpp"
#include "net/packet/qt/serializer.hpp"

class QtPacketWorker : public QObject {
        Q_OBJECT
    public:
        QtPacketWorker(qintptr socketDescriptor);
        QtPacketWorker(QTcpSocket *socket);

        ~QtPacketWorker();

    public slots:
        void connect(std::string hostAddress, uint16_t port);
        void writePacket(BasePacketRef basePacket);

    signals:
        void connected();
        void disconnected();

        void packetRead(BasePacketRef basePacket);

    protected:
        QTcpSocket *m_Socket;
        QtPacketSerializer m_PacketSerializer;

    protected slots:
        void onReadyRead();
};

class QtThreadedPacketWorker : public QObject {
        Q_OBJECT
    public:
        QtThreadedPacketWorker(qintptr socketDescriptor);
        QtThreadedPacketWorker(QTcpSocket *socket);

        ~QtThreadedPacketWorker();

        void connect(std::string hostAddress, uint16_t port);
        void writePacket(BasePacketRef basePacket);

    signals:
        void packetRead(BasePacketRef basePacket);

        void connected();
        void disconnected();

    protected:
        QThread *m_Thread;
        QtPacketWorker *m_PacketWorker;
};
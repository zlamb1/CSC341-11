#include <memory>

#include "net/packet/base.hpp"
#include "net/packet/msg.hpp"
#include "worker.hpp"

QtPacketWorker::QtPacketWorker(qintptr socketDescriptor) {
    m_Socket = new QTcpSocket;
    m_Socket->setSocketDescriptor(socketDescriptor);
    m_Socket->setParent(this);
    QObject::connect(m_Socket, &QAbstractSocket::connected, this,
                     &QtPacketWorker::connected);
    QObject::connect(m_Socket, &QAbstractSocket::disconnected, this,
                     &QtPacketWorker::disconnected);
    QObject::connect(m_Socket, &QAbstractSocket::readyRead, this,
                     &QtPacketWorker::onReadyRead);
}

QtPacketWorker::QtPacketWorker(QTcpSocket *socket) : m_Socket(socket) {
    m_Socket->setParent(this);
    QObject::connect(m_Socket, &QAbstractSocket::connected, this,
                     &QtPacketWorker::connected);
    QObject::connect(m_Socket, &QAbstractSocket::disconnected, this,
                     &QtPacketWorker::disconnected);
    QObject::connect(m_Socket, &QAbstractSocket::readyRead, this,
                     &QtPacketWorker::onReadyRead);
}

QtPacketWorker::~QtPacketWorker() {
    delete m_Socket;
}

void QtPacketWorker::connect(std::string hostAddress, uint16_t port) {
    // NOLINTBEGIN
    QMetaObject::invokeMethod(this, [=]() {
        QHostAddress qHostAddress;
        qHostAddress.setAddress(QString::fromStdString(hostAddress));
        m_Socket->connectToHost(qHostAddress, port);
    });
    // NOLINTEND
}

void QtPacketWorker::writePacket(BasePacketRef basePacket) {
    // NOLINTBEGIN
    QMetaObject::invokeMethod(this, [this, basePacket]() {
        m_PacketSerializer.serialize(m_Socket, basePacket);
    });
    // NOLINTEND
}

void QtPacketWorker::onReadyRead() {
    bool ready;
    auto basePacket = m_PacketSerializer.deserialize(m_Socket, &ready);

    if (!basePacket) {
        if (ready) {
            // FIXME: handle this
            m_Socket->close();
        }
        // not enough data received yet to deserialize packet
        return;
    }

    switch (basePacket->packetType()) {
    case PacketType::MessageSend: {
        auto packet = std::dynamic_pointer_cast<MessageSendPacket>(basePacket);
        break;
    }
    default:
        break;
    }

    emit packetRead(basePacket);

    if (m_Socket->bytesAvailable())
        onReadyRead();
}

QtThreadedPacketWorker::QtThreadedPacketWorker(qintptr socketDescriptor) {
    m_Thread       = new QThread;
    m_PacketWorker = new QtPacketWorker(socketDescriptor);
    m_PacketWorker->moveToThread(m_Thread);
    QObject::connect(m_PacketWorker, &QtPacketWorker::connected, this,
                     &QtThreadedPacketWorker::connected);
    QObject::connect(m_PacketWorker, &QtPacketWorker::disconnected, this,
                     &QtThreadedPacketWorker::disconnected);
    QObject::connect(m_PacketWorker, &QtPacketWorker::packetRead, this,
                     &QtThreadedPacketWorker::packetRead);
    m_Thread->start();
}

QtThreadedPacketWorker::QtThreadedPacketWorker(QTcpSocket *socket) {
    m_Thread       = new QThread;
    m_PacketWorker = new QtPacketWorker(socket);
    m_PacketWorker->moveToThread(m_Thread);
    QObject::connect(m_PacketWorker, &QtPacketWorker::connected, this,
                     &QtThreadedPacketWorker::connected);
    QObject::connect(m_PacketWorker, &QtPacketWorker::disconnected, this,
                     &QtThreadedPacketWorker::disconnected);
    QObject::connect(m_PacketWorker, &QtPacketWorker::packetRead, this,
                     &QtThreadedPacketWorker::packetRead);
    m_Thread->start();
}

QtThreadedPacketWorker::~QtThreadedPacketWorker() {
    m_Thread->quit();
    m_Thread->wait();
    m_Thread->deleteLater();
    m_PacketWorker->deleteLater();
}

void QtThreadedPacketWorker::connect(std::string hostAddress, uint16_t port) {
    m_PacketWorker->connect(hostAddress, port);
}

void QtThreadedPacketWorker::writePacket(BasePacketRef basePacket) {
    m_PacketWorker->writePacket(basePacket);
}
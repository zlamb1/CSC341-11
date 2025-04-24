#pragma once

#include <QTcpSocket>
#include <qglobal.h>
#include <qtcpsocket.h>

#include "net/packet/base.hpp"

class IQtPacketSerializer {
    public:
        virtual uint8_t readUnsignedInt8(QByteArray &byteArray,
                                         uint32_t index = 0);
        virtual uint8_t readUnsignedInt8(QTcpSocket *socket);
        virtual int8_t readInt8(QByteArray &byteArray, uint32_t index = 0);
        virtual int8_t readInt8(QTcpSocket *socket);
        virtual uint32_t readUnsignedInt32(QByteArray &byteArray,
                                           uint32_t index = 0);
        virtual uint32_t readUnsignedInt32(QTcpSocket *socket);
        virtual int32_t readInt32(QByteArray &byteArray, uint32_t index = 0);
        virtual int32_t readInt32(QTcpSocket *socket);

        virtual void writeUnsignedInt8(QByteArray &byteArray, uint8_t i);
        virtual void writeInt8(QByteArray &byteArray, int8_t i);
        virtual void writeUnsignedInt32(QByteArray &byteArray, uint32_t i);
        virtual void writeInt32(QByteArray &byteArray, int32_t i);
        virtual void writeString(QByteArray &byteArray, const std::string &s);

        virtual void serialize(QTcpSocket *socket,
                               BasePacketRef basePacket) = 0;

        virtual BasePacketRef deserialize(QTcpSocket *socket, bool *ready) = 0;
};

class QtPacketSerializer : public IQtPacketSerializer {
    public:
        virtual void serialize(QTcpSocket *socket,
                               BasePacketRef basePacket) override;
        virtual BasePacketRef deserialize(QTcpSocket *socket,
                                          bool *ready) override;

    protected:
        virtual std::string readString(QByteArray &byteArray, bool *malformed,
                                       uint32_t minLength = 1,
                                       uint32_t maxLength = 64);
};
#include <memory>
#include <string>

#include <QDateTime>
#include <QtCore>
#include <QtEndian>

#include "data/msg.hpp"
#include "net/packet/base.hpp"
#include "net/packet/keepalive.hpp"
#include "net/packet/msg.hpp"
#include "net/packet/user.hpp"
#include "serializer.hpp"

constexpr uint32_t MIN_PACKET_LEN = 10;
constexpr uint32_t MAX_PACKET_LEN = 1024;

constexpr uint8_t PACKET_START_SIGNATURE = 0xAB;
constexpr uint8_t PACKET_END_SIGNATURE   = 0x88;

static inline MessageTime qDateTimeToMessageTime(QDateTime qDateTime) {
    return MessageTime{
        std::chrono::milliseconds{qDateTime.toMSecsSinceEpoch()}};
}

static inline QDateTime messageTimeToQDateTime(MessageTime messageTime) {
    return QDateTime::fromMSecsSinceEpoch(
        messageTime.time_since_epoch().count());
}

uint8_t IQtPacketSerializer::readUnsignedInt8(QByteArray &byteArray,
                                              uint32_t index) {
    uint8_t tmp = qFromBigEndian<uint8_t>(((uint8_t *)byteArray.data())[index]);
    byteArray.remove(index, 1);
    return tmp;
}

uint8_t IQtPacketSerializer::readUnsignedInt8(QTcpSocket *socket) {
    auto byteArray = socket->read(1);
    return readUnsignedInt8(byteArray);
}

int8_t IQtPacketSerializer::readInt8(QByteArray &byteArray, uint32_t index) {
    int8_t tmp = qFromBigEndian<int8_t>(((int8_t *)byteArray.data())[index]);
    byteArray.remove(index, 1);
    return tmp;
}

int8_t IQtPacketSerializer::readInt8(QTcpSocket *socket) {
    auto byteArray = socket->read(1);
    return readInt8(byteArray);
}

uint32_t IQtPacketSerializer::readUnsignedInt32(QByteArray &byteArray,
                                                uint32_t index) {
    uint32_t tmp =
        qFromBigEndian<uint32_t>(((uint32_t *)byteArray.data())[index]);
    byteArray.remove(index, 4);
    return tmp;
}

uint32_t IQtPacketSerializer::readUnsignedInt32(QTcpSocket *socket) {
    auto byteArray = socket->read(4);
    return readUnsignedInt32(byteArray);
}

int32_t IQtPacketSerializer::readInt32(QByteArray &byteArray, uint32_t index) {
    int32_t tmp = qFromBigEndian<int32_t>(((int32_t *)byteArray.data())[index]);
    byteArray.remove(index, 4);
    return tmp;
}

int32_t IQtPacketSerializer::readInt32(QTcpSocket *socket) {
    auto byteArray = socket->read(4);
    return readInt32(byteArray);
}

void IQtPacketSerializer::writeUnsignedInt8(QByteArray &byteArray, uint8_t i) {
    byteArray.append(i);
}

void IQtPacketSerializer::writeInt8(QByteArray &byteArray, int8_t i) {
    byteArray.append(i);
}

void IQtPacketSerializer::writeUnsignedInt32(QByteArray &byteArray,
                                             uint32_t i) {
    uint32_t bigEndianI = qToBigEndian(i);
    byteArray.append((char *)(&bigEndianI), 4);
}

void IQtPacketSerializer::writeInt32(QByteArray &byteArray, int32_t i) {
    int32_t bigEndianI = qToBigEndian(i);
    byteArray.append((char *)(&bigEndianI), 4);
}

void IQtPacketSerializer::writeString(QByteArray &byteArray,
                                      const std::string &s) {
    uint32_t size = s.size();
    writeUnsignedInt32(byteArray, size);
    byteArray.append(s.data(), size);
}

void QtPacketSerializer::serialize(QTcpSocket *socket,
                                   BasePacketRef basePacket) {
    QByteArray byteArray;
    writeUnsignedInt8(byteArray, PACKET_START_SIGNATURE);

    qsizetype lengthIndex = byteArray.size();
    // write placeholder packet length
    writeUnsignedInt32(byteArray, 0);

    uint32_t packetTypeAsUint32 =
        static_cast<uint32_t>(basePacket->packetType());
    writeUnsignedInt32(byteArray, packetTypeAsUint32);

    switch (basePacket->packetType()) {
    case PacketType::KeepAlive: {
        auto packet = std::dynamic_pointer_cast<KeepAlivePacket>(basePacket);
        uint32_t status = static_cast<uint32_t>(packet->status());
        writeUnsignedInt32(byteArray, status);
        break;
    }
    case PacketType::UserConnect: {
        auto packet = std::dynamic_pointer_cast<UserConnectPacket>(basePacket);
        writeString(byteArray, packet->name());
        writeUnsignedInt8(byteArray, packet->isSelf());
        break;
    }
    case PacketType::MessageReceive: {
        auto packet =
            std::dynamic_pointer_cast<MessageReceivePacket>(basePacket);
        writeString(byteArray, packet->text());
        writeString(byteArray, packet->sender());
        break;
    }
    case PacketType::MessageSend: {
        auto packet = std::dynamic_pointer_cast<MessageSendPacket>(basePacket);
        writeString(byteArray, packet->text());
        break;
    }
    case PacketType::UserDisconnect: {
        auto packet =
            std::dynamic_pointer_cast<UserDisconnectPacket>(basePacket);
        writeString(byteArray, packet->name());
        break;
    }
    default:
        break;
    }

    byteArray.append(PACKET_END_SIGNATURE);

    uint32_t *packetLength = (uint32_t *)(byteArray.data() + lengthIndex);
    *packetLength = qToBigEndian<uint32_t>(byteArray.size() - lengthIndex - 4);

    qsizetype totalSize   = byteArray.size();
    qint64 bytesRemaining = totalSize;
    while (bytesRemaining) {
        qint64 bytesWritten =
            socket->write(byteArray.sliced(totalSize - bytesRemaining));
        // error occured
        if (bytesWritten < 0)
            break;
        // ???
        if (bytesWritten > bytesRemaining)
            break;
        bytesRemaining -= bytesWritten;
    }
}

BasePacketRef QtPacketSerializer::deserialize(QTcpSocket *socket, bool *ready) {
    *ready = true;

    if (socket->bytesAvailable() < MIN_PACKET_LEN) {
        *ready = false;
        return nullptr;
    }

    auto startBytes = socket->peek(5);

    if (readUnsignedInt8(startBytes) != PACKET_START_SIGNATURE)
        return nullptr;

    uint32_t packetLength = readUnsignedInt32(startBytes);

    if (packetLength > MAX_PACKET_LEN)
        return nullptr;

    if (socket->bytesAvailable() - 5 < packetLength) {
        *ready = false;
        return nullptr;
    }

    // discard already read bytes
    socket->read(5);

    QByteArray data;
    if (packetLength)
        data = socket->read(packetLength);

    BasePacketRef packet = nullptr;

    if (packetLength) {
        PacketType packetType =
            static_cast<PacketType>(readUnsignedInt32(data));
        switch (packetType) {
        case PacketType::KeepAlive: {
            KeepAliveStatus status =
                static_cast<KeepAliveStatus>(readUnsignedInt32(data));
            switch (status) {
            case KeepAliveStatus::Online:
            case KeepAliveStatus::Idle:
                break;
            default:
                return nullptr;
            }
            packet = CreatePacketRef<KeepAlivePacket>(status);
            break;
        }
        case PacketType::UserConnect: {
            bool malformed;
            auto name = readString(data, &malformed);
            if (malformed)
                return nullptr;
            bool self = readUnsignedInt8(data);
            packet    = CreatePacketRef<UserConnectPacket>(name, self);
            break;
        }
        case PacketType::MessageReceive: {
            bool malformed;
            auto text = readString(data, &malformed);
            if (malformed)
                return nullptr;
            auto name = readString(data, &malformed);
            if (malformed)
                return nullptr;
            packet = CreatePacketRef<MessageReceivePacket>(text, name);
            break;
        }
        case PacketType::MessageSend: {
            bool malformed;
            auto text = readString(data, &malformed);
            if (malformed)
                return nullptr;
            packet = CreatePacketRef<MessageSendPacket>(text);
            break;
        };
        case PacketType::UserDisconnect: {
            bool malformed;
            auto name = readString(data, &malformed);
            if (malformed)
                return nullptr;
            packet = CreatePacketRef<UserDisconnectPacket>(name);
            break;
        }
        default:
            break;
        }
    }

    if (readUnsignedInt8(data) != PACKET_END_SIGNATURE)
        return nullptr;

    return packet;
}

std::string QtPacketSerializer::readString(QByteArray &byteArray,
                                           bool *malformed,
                                           uint32_t minimumLength,
                                           uint32_t maximumLength) {
    *malformed = false;

    if (byteArray.length() < 4) {
        *malformed = true;
        return "";
    }

    uint32_t strLength = readUnsignedInt32(byteArray);

    if (strLength < minimumLength || strLength > maximumLength) {
        *malformed = true;
        return "";
    }

    auto str = std::string(byteArray, strLength);
    byteArray.remove(0, strLength);
    return str;
}
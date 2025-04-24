#pragma once

#include <memory>
#include <stdint.h>

enum class PacketType : uint32_t {
    KeepAlive      = 0,
    UserConnect    = 1,
    UserDisconnect = 2,
    MessageReceive = 3,
    MessageSend    = 4
};

struct BasePacket {
    public:
        BasePacket(PacketType packetType) : m_PacketType(packetType) {}
        virtual ~BasePacket() = default;

        PacketType packetType() const {
            return m_PacketType;
        }

    protected:
        PacketType m_PacketType;
};

using BasePacketRef = std::shared_ptr<BasePacket>;

template <typename T, typename... Args>
constexpr std::shared_ptr<T> CreatePacketRef(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

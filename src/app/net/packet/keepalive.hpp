#pragma once

#include "base.hpp"

enum class KeepAliveStatus : int {
    Online = 1,
    Idle   = 2,
};

struct KeepAlivePacket : public BasePacket {
    public:
        KeepAlivePacket(KeepAliveStatus keepAliveStatus)
            : BasePacket(PacketType::KeepAlive), m_Status(keepAliveStatus) {}

        KeepAliveStatus status() const {
            return m_Status;
        }

    protected:
        KeepAliveStatus m_Status;
};
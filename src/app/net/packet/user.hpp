#pragma once

#include <string>

#include "base.hpp"

struct UserConnectPacket : public BasePacket {
    public:
        UserConnectPacket(std::string name, bool self = false)
            : BasePacket(PacketType::UserConnect), m_Name(name), m_Self(self) {}

        const std::string &name() {
            return m_Name;
        }

        bool isSelf() const {
            return m_Self;
        }

    protected:
        std::string m_Name;
        bool m_Self;
};

struct UserDisconnectPacket : public BasePacket {
    public:
        UserDisconnectPacket(std::string name)
            : BasePacket(PacketType::UserDisconnect), m_Name(name) {}

        const std::string &name() {
            return m_Name;
        }

    protected:
        std::string m_Name;
};
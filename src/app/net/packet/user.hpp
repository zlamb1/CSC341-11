#pragma once

#include <string>

#include "base.hpp"

struct UserConnectPacket : public BasePacket {
    public:
        UserConnectPacket(std::string name)
            : BasePacket(PacketType::UserConnect), m_Name(name) {}

        const std::string &name() {
            return m_Name;
        }

    protected:
        std::string m_Name;
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
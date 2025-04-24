#pragma once

#include <string>

#include "base.hpp"
#include "data/msg.hpp"

struct MessageReceivePacket : public BasePacket {
    public:
        MessageReceivePacket(std::string text, std::string sender)
            : BasePacket(PacketType::MessageReceive), m_Text(text),
              m_Sender(sender) {}

        std::string text() const {
            return m_Text;
        }

        std::string sender() const {
            return m_Sender;
        }

    protected:
        std::string m_Text;
        std::string m_Sender;
        MessageTime m_MessageTime;
};

struct MessageSendPacket : public BasePacket {
    public:
        MessageSendPacket(std::string text)
            : BasePacket(PacketType::MessageSend), m_Text(text) {}

        std::string text() const {
            return m_Text;
        }

    protected:
        std::string m_Text;
};
#pragma once

#include <string>

#include "base.hpp"
#include "data/msg.hpp"
#include "data/user.hpp"

struct MessageSendPacket : public BasePacket {
    public:
        MessageSendPacket(std::string text, UserRef sender,
                          MessageTime messageTime)
            : BasePacket(PacketType::MessageSend), m_Text(text),
              m_Sender(sender), m_MessageTime(messageTime) {}

        std::string text() const {
            return m_Text;
        }

        UserRef sender() const {
            return m_Sender;
        }

        MessageTime messageTime() const {
            return m_MessageTime;
        }

    protected:
        std::string m_Text;
        UserRef m_Sender;
        MessageTime m_MessageTime;
};
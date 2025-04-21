#pragma once

#include "data/msg.hpp"
#include "event/event.hpp"

class MessageEvent : public Event {
    public:
        MessageEvent(MessageRef message) : m_Message(message) {}

        MessageRef message() const {
            return m_Message;
        }

    protected:
        MessageRef m_Message;
};

class MessageSendEvent : public Event {
    public:
        MessageSendEvent(const std::string &text) : m_Text(text) {}

        const std::string &text() const;

    protected:
        std::string m_Text;
};
#pragma once

#include <chrono>
#include <memory>

#include "data/user.hpp"

template <class Duration>
using sys_time = std::chrono::time_point<std::chrono::system_clock, Duration>;

using MessageTime = sys_time<std::chrono::milliseconds>;

inline MessageTime GetSystemClockNow() {
    return std::chrono::time_point_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now());
}

class Message {
    public:
        Message(std::string text, UserRef sender,
                MessageTime messageTime = GetSystemClockNow())
            : m_Text(text), m_Sender(sender), m_MessageTime(messageTime) {}

        const std::string &text() const {
            return m_Text;
        };

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

    private:
};

using MessageRef = std::shared_ptr<Message>;
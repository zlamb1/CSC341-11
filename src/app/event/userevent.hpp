#pragma once

#include <memory>

#include "data/user.hpp"
#include "event/event.hpp"

class UserEvent : public Event {
    public:
        UserEvent(std::shared_ptr<User> user) : m_User(user) {}
        std::shared_ptr<User> user() const {
            return m_User;
        }

    private:
        std::shared_ptr<User> m_User;
};
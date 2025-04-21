#pragma once

#include "data/msg_repo.hpp"
#include "data/user.hpp"

/**
 * Decoupled from QT
 */

class MainView {
    public:
        virtual void addUser(UserRef userRef) = 0;
        virtual void deleteUser(UserRef userRef) = 0;

        virtual MessageRepositoryRef messageRepository() const = 0;
        virtual void setMessageRepository(MessageRepositoryRef messageRepo) = 0;

        virtual void
        setMessageHandler(std::function<void(std::string)> handler) = 0;

        virtual void clearMessageText() = 0;
};
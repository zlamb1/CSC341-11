#pragma once

#include "data/msgrepo.hpp"
#include "data/user.hpp"

/**
 * Decoupled from QT
 */

class MainView {
    public:
        virtual ~MainView() = default;

        virtual void show() = 0;

        virtual void showMenuView() = 0;
        virtual void showChatView() = 0;

        virtual void addUser(UserRef userRef)    = 0;
        virtual void deleteUser(UserRef userRef) = 0;

        virtual IMessageRepositoryRef messageRepository() const = 0;
        virtual void
        setMessageRepository(IMessageRepositoryRef messageRepo) = 0;

        virtual void setHostHandler(std::function<void()> hostHandler) = 0;
        virtual void
        setConnectHandler(std::function<void()> connectHandler) = 0;

        virtual void
        setMessageHandler(std::function<void(std::string)> handler) = 0;

        virtual void clearMessageText() = 0;
};
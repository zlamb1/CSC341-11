#include "service/userservice.hpp"
#include "event/handler.hpp"
#include "event/userevent.hpp"
#include <iostream>

UserRef UserService::activeUser() {
    return m_ActiveUser;
}

void UserService::setActiveUser(UserRef activeUser) {
    m_ActiveUser = activeUser;
}

UserRef UserService::user(const std::string &name) {
    if (m_UserMap.count(name))
        return m_UserMap[name];
    return nullptr;
}

const std::vector<UserRef> &UserService::users() const {
    return m_Users;
}

UserCreateResult UserService::createUser(const std::string &name) {
    if (m_UserMap.count(name))
        return UserCreateResult::UNIQUE_NAME_REQIRED;

    auto user       = m_Users.emplace_back(std::make_shared<User>(name));
    m_UserMap[name] = user;

    UserEvent userEvent(user);

    auto iter = m_UserAddHandlers.begin();
    while (iter != m_UserAddHandlers.begin()) {
        if (auto handlerRef = iter->lock()) {
            handlerRef->onEvent(userEvent);
            iter++;
        } else {
            iter = m_UserAddHandlers.erase(iter);
        }
    }

    for (auto handler : m_UserAddHandlers) {
        if (auto handlerRef = handler.lock()) {
            handlerRef->onEvent(userEvent);
        }
    }

    return UserCreateResult::SUCCESS;
}

bool UserService::deleteUser(const std::string &name) {
    if (m_UserMap.count(name)) {
        auto user = m_UserMap[name];
        m_UserMap.erase(name);

        for (auto iter = m_Users.begin(); iter != m_Users.end(); iter++) {
            if (iter->get()->name() == name) {
                m_Users.erase(iter);
                break;
            }
        }

        UserEvent userEvent(user);
        for (auto handler : m_UserDeleteHandlers) {
            if (auto handlerRef = handler.lock()) {
                handlerRef->onEvent(userEvent);
            }
        }

        return true;
    }
    return false;
}

void UserService::addUserAddHandler(HandlerRef<UserEvent> userAddHandler) {
    m_UserAddHandlers.emplace_back(userAddHandler);
}

bool UserService::removeUserAddHandler(HandlerRef<UserEvent> userAddHandler) {
    auto iter = m_UserAddHandlers.begin();
    while (iter != m_UserAddHandlers.end()) {
        auto handlerRef = iter->lock();
        if (!handlerRef)
            iter = m_UserAddHandlers.erase(iter);
        else if (handlerRef == userAddHandler) {
            m_UserAddHandlers.erase(iter);
            return true;
        } else
            iter++;
    }
    return false;
}

void UserService::addUserDeleteHandler(
    HandlerRef<UserEvent> userDeleteHandler) {
    m_UserDeleteHandlers.emplace_back(userDeleteHandler);
}

bool UserService::removeUserDeleteHandler(
    HandlerRef<UserEvent> userDeleteHandler) {
    auto iter = m_UserDeleteHandlers.begin();
    while (iter != m_UserDeleteHandlers.end()) {
        auto handlerRef = iter->lock();
        if (!handlerRef)
            iter = m_UserDeleteHandlers.erase(iter);
        else if (handlerRef == userDeleteHandler) {
            m_UserDeleteHandlers.erase(iter);
            return true;
        } else
            iter++;
    }
    return false;
}
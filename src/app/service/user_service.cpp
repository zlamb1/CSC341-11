#include <memory>

#include "event/handler.hpp"
#include "event/user_event.hpp"
#include "service/user_service.hpp"

UserService::UserService() {
    std::string name = "User #";
    name += std::to_string(rand() % 65536);
    m_ActiveUser = std::make_shared<User>(name);

    m_Users.emplace_back(m_ActiveUser);
    m_UserMap[name] = m_ActiveUser;
}

UserRef UserService::activeUser() {
    return m_ActiveUser;
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

    auto user = m_Users.emplace_back(std::make_shared<User>(name));
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
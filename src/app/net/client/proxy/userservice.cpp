#include <memory>

#include "net/packet/base.hpp"
#include "net/packet/user.hpp"
#include "service/userservice.hpp"
#include "userservice.hpp"

ClientUserService::ClientUserService(IUserServiceRef userService,
                                     INetworkClientRef networkClient)
    : m_UserService(userService), m_NetworkClient(networkClient) {}

UserRef ClientUserService::activeUser() {
    return m_UserService->activeUser();
}

void ClientUserService::setActiveUser(UserRef activeUser) {
    m_UserService->setActiveUser(activeUser);
}

UserRef ClientUserService::user(const std::string &name) {
    return m_UserService->user(name);
}

const std::vector<UserRef> &ClientUserService::users() const {
    return m_UserService->users();
}

UserCreateResult ClientUserService::createUser(const std::string &name) {
    return UserCreateResult::SUCCESS;
}

bool ClientUserService::deleteUser(const std::string &name) {
    return true;
}

void ClientUserService::addUserAddHandler(
    HandlerRef<UserEvent> userAddHandler) {
    m_UserService->addUserAddHandler(userAddHandler);
}

bool ClientUserService::removeUserAddHandler(
    HandlerRef<UserEvent> userAddHandler) {
    return m_UserService->removeUserAddHandler(userAddHandler);
}

void ClientUserService::addUserDeleteHandler(
    HandlerRef<UserEvent> userDeleteHandler) {
    m_UserService->addUserDeleteHandler(userDeleteHandler);
}

bool ClientUserService::removeUserDeleteHandler(
    HandlerRef<UserEvent> userDeleteHandler) {
    return m_UserService->removeUserDeleteHandler(userDeleteHandler);
}

void ClientUserService::handlePacket(PacketRequest *request) {
    auto basePacket = request->packet();
    switch (basePacket->packetType()) {
    case PacketType::UserConnect: {
        request->accept();
        auto userConnectPacket =
            std::dynamic_pointer_cast<UserConnectPacket>(basePacket);
        m_UserService->createUser(userConnectPacket->name());
        break;
    }
    case PacketType::UserDisconnect: {
        request->accept();
        auto userDisconnectPacket =
            std::dynamic_pointer_cast<UserDisconnectPacket>(basePacket);
        m_UserService->deleteUser(userDisconnectPacket->name());
        break;
    }
    default:
        break;
    }
}
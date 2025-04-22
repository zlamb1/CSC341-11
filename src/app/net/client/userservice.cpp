#include "service/userservice.hpp"
#include "net/packet/base.hpp"
#include "net/packet/dest.hpp"
#include "net/packet/user.hpp"
#include "userservice.hpp"

ClientUserService::ClientUserService(IUserServiceRef userService)
    : m_UserService(userService) {}

UserRef ClientUserService::activeUser() {
    return m_UserService->activeUser();
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
    return false;
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
        auto packet = std::dynamic_pointer_cast<UserConnectPacket>(basePacket);
        m_UserService->createUser(packet->name());
        break;
    }
    case PacketType::UserDisconnect: {
        request->accept();
        auto packet =
            std::dynamic_pointer_cast<UserDisconnectPacket>(basePacket);
        m_UserService->deleteUser(packet->name());
        break;
    }
    default:
        break;
    }
}
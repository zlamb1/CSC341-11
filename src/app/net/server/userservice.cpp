#include "userservice.hpp"
#include "net/client/userservice.hpp"
#include "net/packet/base.hpp"
#include "net/packet/user.hpp"

ServerUserService::ServerUserService(IUserServiceRef userService,
                                     INetworkServiceRef networkService)
    : ClientUserService(userService), m_NetworkService(networkService) {}

UserCreateResult ServerUserService::createUser(const std::string &name) {
    if (m_UserService->user(name)) {
        return UserCreateResult::UNIQUE_NAME_REQIRED;
    }

    auto userConnectPacket = CreatePacketRef<UserConnectPacket>(name);
    m_NetworkService->writePacket(userConnectPacket);

    return UserCreateResult::SUCCESS;
}

bool ServerUserService::deleteUser(const std::string &name) {
    if (!m_UserService->user(name)) {
        return false;
    }

    auto userDisconnectPacket = CreatePacketRef<UserDisconnectPacket>(name);
    m_NetworkService->writePacket(userDisconnectPacket);

    return true;
}

void ServerUserService::handlePacket(PacketRequest *request) {
    auto basePacket = request->packet();
    switch (basePacket->packetType()) {
    case PacketType::KeepAlive:
        request->accept();
        // FIXME: handle
        break;
    default:
        // on server: only handle authoritative packets from server
        if (request->packetSender() == activeUser()) {
            ClientUserService::handlePacket(request);
        }
        break;
    }
}
#pragma once

#include "net/client/userservice.hpp"
#include "net/networkservice.hpp"
#include "service/userservice.hpp"

class ServerUserService : public ClientUserService {
    public:
        ServerUserService(IUserServiceRef userService,
                          INetworkServiceRef networkService);

        virtual UserCreateResult createUser(const std::string &name) override;
        virtual bool deleteUser(const std::string &name) override;

        virtual void handlePacket(PacketRequest *request) override;

    protected:
        INetworkServiceRef m_NetworkService;
};
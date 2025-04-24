#pragma once

#include "net/client/networkclient.hpp"
#include "net/packet/dest.hpp"
#include "service/userservice.hpp"

class ClientUserService : public UserService, public PacketHandler {
    public:
        ClientUserService(IUserServiceRef userService,
                          INetworkClientRef networkClient);
        virtual ~ClientUserService() = default;

        virtual UserRef activeUser() override;
        virtual void setActiveUser(UserRef activeUser) override;

        virtual UserRef user(const std::string &name) override;

        virtual const std::vector<UserRef> &users() const override;

        virtual UserCreateResult createUser(const std::string &name) override;
        virtual bool deleteUser(const std::string &name) override;

        virtual void
        addUserAddHandler(HandlerRef<UserEvent> userAddHandler) override;
        virtual bool
        removeUserAddHandler(HandlerRef<UserEvent> userAddHandler) override;

        virtual void
        addUserDeleteHandler(HandlerRef<UserEvent> userDeleteHandler) override;
        virtual bool removeUserDeleteHandler(
            HandlerRef<UserEvent> userDeleteHandler) override;

        virtual void handlePacket(PacketRequest *request) override;

    protected:
        IUserServiceRef m_UserService;
        INetworkClientRef m_NetworkClient;
};
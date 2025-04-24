#pragma once

#include "data/msgrepo.hpp"
#include "net/client/networkclient.hpp"
#include "net/packet/dest.hpp"
#include "service/userservice.hpp"

/**
 * @Pattern Proxy
 */

class ClientMessageRepository : public IMessageRepository,
                                public PacketHandler {
    public:
        ClientMessageRepository(IMessageRepositoryRef messageRepo,
                                IUserServiceRef userService,
                                INetworkClientRef networkService);
        virtual ~ClientMessageRepository() = default;

        virtual RepositoryType repositoryType() const override;
        virtual const std::vector<MessageRef> &messages() const override;

        virtual void
        createMessage(std::string text, UserRef sender,
                      MessageTime messageTime = GetSystemClockNow()) override;

        virtual void addMessageAddHandler(
            HandlerRef<MessageEvent> messageAddHandler) override;

        virtual bool removeMessageAddHandler(
            HandlerRef<MessageEvent> messageAddHandler) override;

        virtual void handlePacket(PacketRequest *request) override;

    protected:
        IMessageRepositoryRef m_MessageRepo;
        IUserServiceRef m_UserService;
        INetworkClientRef m_NetworkClient;
};
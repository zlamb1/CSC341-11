#pragma once

#include "data/msg.hpp"
#include "data/msgrepo.hpp"
#include "net/networkservice.hpp"
#include "net/packet/dest.hpp"

/**
 * @Pattern Proxy
 */

class ClientMessageRepository : public IMessageRepository, PacketDestination {
    public:
        ClientMessageRepository(IMessageRepositoryRef messageRepo,
                                INetworkServiceRef networkService);

        virtual RepositoryType repositoryType() const override;
        virtual const std::vector<MessageRef> &messages() const override;

        virtual void createMessage(std::string text, UserRef sender) override;
        virtual void createMessage(std::string text, UserRef sender,
                                   MessageTime messageTime) override;

        virtual void addMessageAddHandler(
            HandlerRef<MessageEvent> messageAddHandler) override;

        virtual bool removeMessageAddHandler(
            HandlerRef<MessageEvent> messageAddHandler) override;

        virtual void handlePacket(PacketRequest *request) override;

    protected:
        IMessageRepositoryRef m_MessageRepo;
        INetworkServiceRef m_NetworkService;
};
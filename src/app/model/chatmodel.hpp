#pragma once

#include "model/appmodel.hpp"
#include "net/client/networkclient.hpp"
#include "net/server/networkserver.hpp"
#include "service/userservice.hpp"

class ChatAppModel : public IAppModel {
    public:
        ChatAppModel();
        virtual ~ChatAppModel() = default;

        virtual void sendMessage(std::string text) override;

        virtual void connectToHost(std::string hostAddress,
                                   uint16_t port) override;
        virtual void hostServer(std::string hostAddress,
                                uint16_t port) override;

    protected:
        IUserServiceRef m_UserService;
        IMessageRepositoryRef m_GlobalMessageRepository;

        INetworkServerRef m_NetworkServer;
        INetworkClientRef m_NetworkClient;

        HandlerRef<UserEvent> m_UserAddHandler;
        HandlerRef<UserEvent> m_UserDeleteHandler;

        HandlerRef<MessageEvent> m_MessageAddHandler;

        void createClient(std::string hostAddress, uint16_t port);
};
#pragma once

#include "data/msgrepo.hpp"
#include "net/client/networkclient.hpp"
#include "net/server/networkserver.hpp"
#include "service/userservice.hpp"
#include "ui/mainview.hpp"

class ChatApp {

    public:
        ChatApp(int argc, char *argv[]);
        ~ChatApp();

    protected:
        IUserServiceRef m_UserService;
        IMessageRepositoryRef m_GlobalMessageRepo;

        INetworkServerRef m_NetworkServer;
        INetworkClientRef m_NetworkClient;

        MainView *m_MainView;

        void connectWithClient();
};
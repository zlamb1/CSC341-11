#include <QApplication>
#include <memory>
#include <string>

#include "chatapp.hpp"
#include "mainwindow.hpp"
#include "net/client/proxy/msgrepo.hpp"
#include "net/client/proxy/userservice.hpp"
#include "net/client/qt/networkclient.hpp"
#include "net/server/qt/networkserver.hpp"
#include "service/userservice.hpp"

ChatApp::ChatApp(int argc, char *argv[]) {
    QApplication app(argc, argv);

    srand(time(0));

    m_UserService = std::make_shared<UserService>();
    m_GlobalMessageRepo =
        std::make_shared<MessageRepository>(RepositoryType::GLOBAL);

    m_MainView = new MainWindow;
    m_MainView->show();

    auto userAddHandler = CreateHandler<UserEvent>(
        [&](auto event) { m_MainView->addUser(event.user()); });
    auto userDeleteHandler = CreateHandler<UserEvent>(
        [&](auto event) { m_MainView->deleteUser(event.user()); });

    m_UserService->addUserAddHandler(userAddHandler);
    m_UserService->addUserDeleteHandler(userDeleteHandler);

    m_MainView->setMessageRepository(m_GlobalMessageRepo);

    m_MainView->setHostHandler([&] {
        m_NetworkServer = std::make_shared<QtNetworkServer>(m_UserService);
        m_NetworkServer->listen("127.0.0.1", 9090);

        connectWithClient();

        m_MainView->showChatView();
    });

    m_MainView->setConnectHandler([&]() {
        connectWithClient();
        m_MainView->showChatView();
    });

    m_MainView->setMessageHandler([&](std::string text) {
        if (auto repo = m_MainView->messageRepository()) {
            repo->createMessage(text, m_UserService->activeUser());
            m_MainView->clearMessageText();
        }
    });

    app.exec();
}

ChatApp::~ChatApp() {
    delete m_MainView;
}

void ChatApp::connectWithClient() {
    std::string name = "User #";
    name += std::to_string(rand() % 65356);

    m_NetworkClient = std::make_shared<QtNetworkClient>(name, m_UserService);
    m_NetworkClient->connect("127.0.0.1", 9090);

    auto wrapperUserService =
        std::make_shared<ClientUserService>(m_UserService, m_NetworkClient);
    auto wrapperMessageRepo = std::make_shared<ClientMessageRepository>(
        m_GlobalMessageRepo, wrapperUserService, m_NetworkClient);

    m_NetworkClient->addPacketHandler(wrapperUserService);
    m_NetworkClient->addPacketHandler(wrapperMessageRepo);

    m_MainView->setMessageRepository(wrapperMessageRepo);
}
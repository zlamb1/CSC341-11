#include "chatmodel.hpp"
#include "event/handler.hpp"
#include "event/msgevent.hpp"
#include "net/client/proxy/msgrepo.hpp"
#include "net/client/proxy/userservice.hpp"
#include "net/client/qt/networkclient.hpp"
#include "net/server/qt/networkserver.hpp"

ChatAppModel::ChatAppModel() {
    m_UserService = std::make_shared<UserService>();
    m_GlobalMessageRepository =
        std::make_shared<MessageRepository>(RepositoryType::GLOBAL);

    setActiveMessageRepository(m_GlobalMessageRepository);

    m_UserAddHandler = CreateHandler<UserEvent>([this](auto event) {
        if (m_UserAddNotifier)
            m_UserAddNotifier(event.user());
    });

    m_UserDeleteHandler = CreateHandler<UserEvent>([this](auto event) {
        if (m_UserDeleteNotifier)
            m_UserDeleteNotifier(event.user());
    });

    m_MessageAddHandler = CreateHandler<MessageEvent>([this](auto event) {
        if (m_MessageAddNotifier)
            m_MessageAddNotifier(event.message());
    });

    m_UserService->addUserAddHandler(m_UserAddHandler);
    m_UserService->addUserDeleteHandler(m_UserDeleteHandler);

    m_GlobalMessageRepository->addMessageAddHandler(m_MessageAddHandler);
}

void ChatAppModel::sendMessage(std::string text) {
    if (m_ActiveMessageRepository) {
        m_ActiveMessageRepository->createMessage(text,
                                                 m_UserService->activeUser());
    }
}

void ChatAppModel::connectToHost(std::string hostAddress, uint16_t port) {
    createClient(hostAddress, port);
}

void ChatAppModel::hostServer(std::string hostAddress, uint16_t port) {
    m_NetworkServer = std::make_shared<QtNetworkServer>(m_UserService);
    m_NetworkServer->listen(hostAddress, port);

    createClient(hostAddress, port);
}

void ChatAppModel::createClient(std::string hostAddress, uint16_t port) {
    std::string name = "User #";
    name += std::to_string(rand() % 65356);

    m_NetworkClient = std::make_shared<QtNetworkClient>(name, m_UserService);

    m_NetworkClient->setConnectHandler([this]() {
        if (m_ClientConnectNotifier)
            m_ClientConnectNotifier();
    });

    m_NetworkClient->setDisconnectHandler([this]() {
        if (m_ClientDisconnectNotifier)
            m_ClientDisconnectNotifier();
    });

    m_NetworkClient->connect(hostAddress, port);

    auto clientUserService =
        std::make_shared<ClientUserService>(m_UserService, m_NetworkClient);
    auto clientMessageRepository = std::make_shared<ClientMessageRepository>(
        m_GlobalMessageRepository, clientUserService, m_NetworkClient);

    m_NetworkClient->addPacketHandler(clientUserService);
    m_NetworkClient->addPacketHandler(clientMessageRepository);

    setActiveMessageRepository(clientMessageRepository);
}
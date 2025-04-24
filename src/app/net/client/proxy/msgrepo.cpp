#include <iostream>
#include <memory>

#include "data/msgrepo.hpp"
#include "msgrepo.hpp"
#include "net/client/networkclient.hpp"
#include "net/packet/base.hpp"
#include "net/packet/msg.hpp"
#include "service/userservice.hpp"

ClientMessageRepository::ClientMessageRepository(
    IMessageRepositoryRef messageRepo, IUserServiceRef userService,
    INetworkClientRef networkClient)
    : m_MessageRepo(messageRepo), m_UserService(userService),
      m_NetworkClient(networkClient) {}

RepositoryType ClientMessageRepository::repositoryType() const {
    return m_MessageRepo->repositoryType();
};

const std::vector<MessageRef> &ClientMessageRepository::messages() const {
    return m_MessageRepo->messages();
}

void ClientMessageRepository::createMessage(std::string text, UserRef sender,
                                            MessageTime messageTime) {
    auto messageSendPacket = CreatePacketRef<MessageSendPacket>(text);
    m_NetworkClient->write(messageSendPacket);
}

void ClientMessageRepository::addMessageAddHandler(
    HandlerRef<MessageEvent> messageAddHandler) {
    m_MessageRepo->addMessageAddHandler(messageAddHandler);
}

bool ClientMessageRepository::removeMessageAddHandler(
    HandlerRef<MessageEvent> messageAddHandler) {
    return m_MessageRepo->removeMessageAddHandler(messageAddHandler);
}

void ClientMessageRepository::handlePacket(PacketRequest *request) {
    auto basePacket = request->packet();
    switch (basePacket->packetType()) {
    case PacketType::MessageReceive: {
        request->accept();
        auto packet =
            std::dynamic_pointer_cast<MessageReceivePacket>(basePacket);

        auto sender = m_UserService->user(packet->sender());
        if (!sender) {
            std::cout << "[ClientMessageRepository] Unknown User in "
                         "MessageSendPacket: "
                      << packet->sender() << "\n";
            return;
        }

        m_MessageRepo->createMessage(packet->text(), sender);
        break;
    }
    default:
        break;
    }
}
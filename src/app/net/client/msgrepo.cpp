#include <memory>

#include "data/msgrepo.hpp"
#include "data/user.hpp"
#include "msgrepo.hpp"
#include "net/packet/msg.hpp"

ClientMessageRepository::ClientMessageRepository(
    IMessageRepositoryRef messageRepo, INetworkServiceRef networkService)
    : m_MessageRepo(messageRepo), m_NetworkService(networkService) {}

RepositoryType ClientMessageRepository::repositoryType() const {
    return m_MessageRepo->repositoryType();
}

const std::vector<MessageRef> &ClientMessageRepository::messages() const {
    return m_MessageRepo->messages();
}

void ClientMessageRepository::createMessage(std::string text, UserRef sender) {
    auto message           = Message(text, sender);
    auto messageSendPacket = CreatePacketRef<MessageSendPacket>(message);
    m_NetworkService->writePacket(messageSendPacket);
}

void ClientMessageRepository::createMessage(std::string text, UserRef sender,
                                            MessageTime messageTime) {
    auto message           = Message(text, sender, messageTime);
    auto messageSendPacket = CreatePacketRef<MessageSendPacket>(message);
    m_NetworkService->writePacket(messageSendPacket);
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
    case PacketType::MessageSend: {
        request->accept();
        auto packet = std::dynamic_pointer_cast<MessageSendPacket>(basePacket);
        m_MessageRepo->createMessage(packet->text(), packet->sender(),
                                     packet->messageTime());
        break;
    }
    default:
        break;
    }
}
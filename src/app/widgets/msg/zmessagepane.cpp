#include <functional>

#include <QVBoxLayout>
#include <qlabel.h>
#include <qnamespace.h>

#include "data/msg_repo.hpp"
#include "event/handler.hpp"
#include "event/msg_event.hpp"
#include "widgets/msg/zmessage.hpp"
#include "widgets/msg/zmessagepane.hpp"

ZMessagePane::ZMessagePane(QWidget *parent) : QWidget(parent) {
    auto addMessageHandler =
        std::bind(&ZMessagePane::onMessage, this, std::placeholders::_1);
    m_MessageAddHandler = CreateHandler<MessageEvent>(addMessageHandler);

    m_Layout = new QVBoxLayout;
    m_Layout->setAlignment(Qt::AlignTop);

    setLayout(m_Layout);
}

MessageRepositoryRef ZMessagePane::messageRepository() const {
    return m_MessageRepo;
}

void ZMessagePane::setMessageRepository(
    MessageRepositoryRef messageRepository) {
    if (m_MessageRepo)
        m_MessageRepo->removeMessageAddHandler(m_MessageAddHandler);
    clearMessages();
    m_MessageRepo = messageRepository;
    if (m_MessageRepo)
        m_MessageRepo->addMessageAddHandler(m_MessageAddHandler);
}

void ZMessagePane::clearMessages() {
    QLayoutItem *item;
    while ((item = m_Layout->takeAt(0)) != nullptr)
        delete item;
}

void ZMessagePane::addMessage(MessageRef message) {
    ZMessage *messageWidget = new ZMessage(message);
    m_Layout->addWidget(messageWidget);
}

void ZMessagePane::onMessage(MessageEvent &event) {
    addMessage(event.message());
}
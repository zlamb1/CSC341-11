#include <functional>

#include <QGridLayout>
#include <QScrollArea>
#include <qlabel.h>
#include <qnamespace.h>

#include "chatview.hpp"
#include "msg/zmessagepane.hpp"
#include "utility/hline.hpp"
#include "utility/vline.hpp"
#include "zbottombar.hpp"
#include "zsidebar.hpp"

ChatView::ChatView(QWidget *parent) : QWidget(parent) {
    m_Layout = new QGridLayout(this);
    m_Layout->setSpacing(0);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setColumnStretch(0, 1);
    m_Layout->setColumnStretch(0, 0);
    m_Layout->setRowStretch(0, 0);
    m_Layout->setRowStretch(1, 1);
    m_Layout->setRowStretch(2, 0);

    m_TopLabel = new QLabel("Chat Room", this);
    m_TopLabel->setAlignment(Qt::AlignCenter);
    m_TopLabel->setStyleSheet("font-weight: bold; font-size: 16px; ");

    m_Layout->addWidget(m_TopLabel, 0, 0, 1, 1);

    m_MessagePane = new ZMessagePane(this);

    m_MessagePaneScrollArea = new QScrollArea(this);
    m_MessagePaneScrollArea->setWidget(m_MessagePane);
    m_MessagePaneScrollArea->setWidgetResizable(true);
    m_MessagePaneScrollArea->setFrameShape(QFrame::NoFrame);

    m_Layout->addWidget(m_MessagePaneScrollArea, 1, 0, 1, 1);

    QColor borderColor = palette().color(QPalette::WindowText);
    borderColor.setAlphaF(0.1F);

    m_SideSeparator = new VLine(this);
    m_SideSeparator->setColor(borderColor);
    m_Layout->addWidget(m_SideSeparator, 0, 1, -1, 1);

    m_SideBar = new ZSideBar(this);
    m_Layout->addWidget(m_SideBar, 0, 2, -1, 1);

    m_BottomSeparator = new HLine(this);
    m_BottomSeparator->setColor(borderColor);
    m_Layout->addWidget(m_BottomSeparator, 2, 0, 1, 1);

    m_BottomBar = new ZBottomBar(this);

    QObject::connect(m_BottomBar, &ZBottomBar::messageSent, this,
                     &ChatView::messageSent);

    m_Layout->addWidget(m_BottomBar, 3, 0, 1, 1);

    setLayout(m_Layout);
}

void ChatView::setChat(UserRef userRef) {
    m_SideBar->setChat(userRef);
}

void ChatView::addUser(UserRef userRef) {
    m_SideBar->addUser(userRef);
}

void ChatView::deleteUser(UserRef userRef) {
    m_SideBar->deleteUser(userRef);
}

void ChatView::setMessageRepository(IMessageRepositoryRef messageRepo) {
    m_MessagePane->setMessageRepository(messageRepo);
}

void ChatView::clearMessageText() {
    m_BottomBar->clearMessageText();
}

void ChatView::setOpenChatHandler(
    std::function<void(std::string)> openChatHandler) {
    m_SideBar->setOpenChatHandler(openChatHandler);
}
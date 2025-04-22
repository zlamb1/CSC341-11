#include <QGridLayout>
#include <QScrollArea>
#include <functional>

#include "chatview.hpp"
#include "msg/zmessagepane.hpp"
#include "utility/hline.hpp"
#include "utility/vline.hpp"
#include "zbottombar.hpp"
#include "zsidebar.hpp"

ChatView::ChatView(const UserService &userService, QWidget *parent)
    : QWidget(parent) {
    m_Layout = new QGridLayout();
    m_Layout->setSpacing(0);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->setColumnStretch(0, 1);
    m_Layout->setColumnStretch(0, 0);
    m_Layout->setRowStretch(0, 1);
    m_Layout->setRowStretch(1, 0);

    m_MessagePane = new ZMessagePane;

    m_MessagePaneScrollArea = new QScrollArea;
    m_MessagePaneScrollArea->setWidget(m_MessagePane);
    m_MessagePaneScrollArea->setWidgetResizable(true);
    m_MessagePaneScrollArea->setFrameShape(QFrame::NoFrame);

    m_Layout->addWidget(m_MessagePaneScrollArea, 0, 0, 1, 1);

    QColor borderColor = palette().color(QPalette::WindowText);
    borderColor.setAlphaF(0.1F);

    m_SideSeparator = new VLine;
    m_SideSeparator->setColor(borderColor);
    m_Layout->addWidget(m_SideSeparator, 0, 1, -1, 1);

    m_SideBar = new ZSideBar(userService);
    m_Layout->addWidget(m_SideBar, 0, 2, -1, 1);

    m_BottomSeparator = new HLine;
    m_BottomSeparator->setColor(borderColor);
    m_Layout->addWidget(m_BottomSeparator, 1, 0, 1, 1);

    m_BottomBar = new ZBottomBar;
    m_Layout->addWidget(m_BottomBar, 2, 0, 1, 1);

    setLayout(m_Layout);
    QObject::connect(m_BottomBar, &ZBottomBar::onSendMessage, this,
                     [this](auto text) {
                         if (m_MessageHandler) {
                             m_MessageHandler(text);
                         }
                     });
}

ChatView::~ChatView() {
    delete m_MessagePane;
    delete m_MessagePaneScrollArea;
    delete m_SideSeparator;
    delete m_BottomSeparator;
    delete m_SideBar;
    delete m_BottomBar;
    delete m_Layout;
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

void ChatView::setMessageHandler(
    std::function<void(std::string)> messageHandler) {
    m_MessageHandler = messageHandler;
}

void ChatView::clearMessageText() {
    m_BottomBar->clearMessageText();
}
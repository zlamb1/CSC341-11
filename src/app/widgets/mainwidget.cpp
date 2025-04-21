#include <QtWidgets>

#include <QLabel>
#include <QLineEdit>
#include <functional>

#include "mainwidget.hpp"

#include "data/msg_repo.hpp"
#include "widgets/msg/zmessagepane.hpp"
#include "widgets/utility/hline.hpp"
#include "widgets/utility/vline.hpp"
#include "widgets/zbottombar.hpp"
#include "widgets/zsidebar.hpp"

MainWidget::MainWidget(const UserService &userService, QWidget *parent)
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

    QColor borderColor(100, 100, 100);

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

    resize(500, 500);
    setLayout(m_Layout);
    setWindowTitle(tr("EmberChat"));
}

MainWidget::~MainWidget() {
    delete m_MessagePane;
    delete m_MessagePaneScrollArea;
    delete m_SideBar;
    delete m_BottomBar;
    delete m_Layout;
}

void MainWidget::addUser(UserRef userRef) {
    m_SideBar->addUser(userRef);
}

void MainWidget::deleteUser(UserRef userRef) {
    m_SideBar->deleteUser(userRef);
}

MessageRepositoryRef MainWidget::messageRepository() const {
    return m_ActiveRepo;
}

void MainWidget::setMessageRepository(MessageRepositoryRef messageRepo) {
    m_ActiveRepo = messageRepo;
    m_MessagePane->setMessageRepository(messageRepo);
}

void MainWidget::setMessageHandler(
    std::function<void(std::string)> messageHandler) {
    m_MessageHandler = messageHandler;
    if (m_MessageHandler) {
        QObject::connect(m_BottomBar, &ZBottomBar::onSendMessage, this,
                         m_MessageHandler);
    }
}

void MainWidget::clearMessageText() {
    m_BottomBar->clearMessageText();
}
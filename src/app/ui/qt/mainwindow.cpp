#include <QtWidgets>

#include <QLabel>
#include <QLineEdit>

#include "mainwindow.hpp"
#include "views/menuview.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_CenterWidget = new QStackedWidget;
    m_MenuView     = new MenuView;
    m_ChatView     = new ChatView;

    m_CenterWidget->addWidget(m_MenuView);
    m_CenterWidget->addWidget(m_ChatView);

    m_CenterWidget->setCurrentWidget(m_MenuView);
    setCentralWidget(m_CenterWidget);

    resize(500, 500);
    setWindowTitle(tr("EmberChat"));
}

MainWindow::~MainWindow() {
    delete m_MenuView;
    delete m_ChatView;
    delete m_CenterWidget;
}

void MainWindow::show() {
    QWidget::show();
}

void MainWindow::showMenuView() {
    m_CenterWidget->setCurrentWidget(m_MenuView);
}

void MainWindow::showChatView() {
    m_CenterWidget->setCurrentWidget(m_ChatView);
}

void MainWindow::addUser(UserRef userRef) {
    m_ChatView->addUser(userRef);
}

void MainWindow::deleteUser(UserRef userRef) {
    m_ChatView->deleteUser(userRef);
}

IMessageRepositoryRef MainWindow::messageRepository() const {
    return m_ActiveRepo;
}

void MainWindow::setMessageRepository(IMessageRepositoryRef messageRepo) {
    m_ChatView->setMessageRepository(messageRepo);
    m_ActiveRepo = messageRepo;
}

void MainWindow::setHostHandler(std::function<void()> hostHandler) {
    if (m_HostHandlerSet)
        QObject::disconnect(m_HostHandler);
    else
        m_HostHandlerSet = true;
    m_HostHandler =
        QObject::connect(m_MenuView, &MenuView::onHost, hostHandler);
}

void MainWindow::setConnectHandler(std::function<void()> connectHandler) {
    if (m_ConnectHandlerSet)
        QObject::disconnect(m_ConnectHandler);
    else
        m_ConnectHandlerSet = true;
    m_ConnectHandler =
        QObject::connect(m_MenuView, &MenuView::onConnect, connectHandler);
}

void MainWindow::setMessageHandler(
    std::function<void(std::string)> messageHandler) {
    m_ChatView->setMessageHandler(messageHandler);
}

void MainWindow::clearMessageText() {
    m_ChatView->clearMessageText();
}
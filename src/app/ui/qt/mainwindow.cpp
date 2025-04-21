#include <QtWidgets>

#include <QLabel>
#include <QLineEdit>
#include <qlabel.h>
#include <qstackedwidget.h>

#include "mainwindow.hpp"

MainWindow::MainWindow(const UserService &userService, QWidget *parent)
    : QMainWindow(parent), m_UserService(userService) {
    m_ChatView = new ChatView(userService);
    QStackedWidget *centerWidget = new QStackedWidget;
    centerWidget->addWidget(m_ChatView);
    centerWidget->setCurrentWidget(m_ChatView);
    setCentralWidget(centerWidget);
    resize(500, 500);
    setWindowTitle(tr("EmberChat"));
}

MainWindow::~MainWindow() {
    delete m_ChatView;
}

void MainWindow::addUser(UserRef userRef) {
    m_ChatView->addUser(userRef);
}

void MainWindow::deleteUser(UserRef userRef) {
    m_ChatView->deleteUser(userRef);
}

MessageRepositoryRef MainWindow::messageRepository() const {
    return m_ActiveRepo;
}

void MainWindow::setMessageRepository(MessageRepositoryRef messageRepo) {
    m_ChatView->setMessageRepository(messageRepo);
    m_ActiveRepo = messageRepo;
}

void MainWindow::setMessageHandler(
    std::function<void(std::string)> messageHandler) {
    m_ChatView->setMessageHandler(messageHandler);
}

void MainWindow::clearMessageText() {
    m_ChatView->clearMessageText();
}
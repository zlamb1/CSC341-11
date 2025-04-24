#include <QtWidgets>

#include <QLabel>
#include <QLineEdit>
#include <qobject.h>

#include "mainwindow.hpp"
#include "views/menuview.hpp"

MainWindow::MainWindow(IAppModel *appModel, QWidget *parent)
    : QMainWindow(parent), IAppView(appModel) {
    m_CenterWidget = new QStackedWidget(this);
    m_MenuView     = new MenuView(this);
    m_ChatView     = new ChatView(this);

    /* CONNECT VIEW TO MODEL */

    m_ChatView->setMessageRepository(m_AppModel->activeMessageRepository());

    m_AppModel->notifyUserAddNotifier(
        [this](auto user) { m_ChatView->addUser(user); });
    m_AppModel->notifyUserDeleteNotifier(
        [this](auto user) { m_ChatView->deleteUser(user); });

    m_AppModel->notifyMessageAddNotifier(
        [this](auto message) { m_ChatView->clearMessageText(); });

    m_AppModel->notifyActiveMessageRepositoryChange(
        [this](auto messageRepository) {
            m_ChatView->setMessageRepository(messageRepository);
        });

    m_AppModel->notifyClientConnectNotifier(
        [this]() { m_CenterWidget->setCurrentWidget(m_ChatView); });

    m_AppModel->notifyClientDisconnectNotifier(
        [this]() { m_CenterWidget->setCurrentWidget(m_MenuView); });

    QObject::connect(m_MenuView, &MenuView::onHost,
                     [this](auto hostAddress, auto port) {
                         m_AppModel->hostServer(hostAddress, port);
                     });

    QObject::connect(m_MenuView, &MenuView::onConnect,
                     [this](auto hostAddress, auto port) {
                         m_AppModel->connectToHost(hostAddress, port);
                     });

    QObject::connect(m_ChatView, &ChatView::messageSent,
                     [this](auto text) { m_AppModel->sendMessage(text); });

    /* LAYOUT VIEW */

    m_CenterWidget->addWidget(m_MenuView);
    m_CenterWidget->addWidget(m_ChatView);

    m_CenterWidget->setCurrentWidget(m_MenuView);
    setCentralWidget(m_CenterWidget);

    resize(500, 500);
    setWindowTitle(tr("EmberChat"));
}

void MainWindow::show() {
    QWidget::show();
}
#pragma once

#include <QMainWindow>
#include <functional>

#include "data/msgrepo.hpp"
#include "data/user.hpp"
#include "ui/mainview.hpp"
#include "views/chatview.hpp"
#include "views/menuview.hpp"

class QGridLayout;
class QLabel;
class QLineEdit;
class QScrollArea;
class QStackedWidget;

class ZSideBar;
class ZBottomBar;
class ZMessagePane;
class ZUserButton;

class HLine;
class VLine;

class MainWindow : public QMainWindow, public MainView {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        virtual ~MainWindow() override;

        virtual void show() override;

        virtual void showMenuView() override;
        virtual void showChatView() override;

        virtual void addUser(UserRef userRef) override;
        virtual void deleteUser(UserRef userRef) override;

        virtual IMessageRepositoryRef messageRepository() const override;

        virtual void
        setMessageRepository(IMessageRepositoryRef messageRepo) override;

        virtual void setHostHandler(std::function<void()> hostHandler) override;
        virtual void
        setConnectHandler(std::function<void()> connectHandler) override;

        virtual void
        setMessageHandler(std::function<void(std::string)> handler) override;

        virtual void clearMessageText() override;

    private:
        QStackedWidget *m_CenterWidget;

        MenuView *m_MenuView;
        ChatView *m_ChatView;

        IMessageRepositoryRef m_ActiveRepo;

        bool m_HostHandlerSet = false, m_ConnectHandlerSet = false;
        QMetaObject::Connection m_HostHandler, m_ConnectHandler;
};
#pragma once

#include <QMainWindow>
#include <functional>

#include "data/msgrepo.hpp"
#include "data/user.hpp"
#include "service/userservice.hpp"
#include "ui/mainview.hpp"
#include "views/chatview.hpp"

class QGridLayout;
class QLabel;
class QLineEdit;
class QScrollArea;

class ZSideBar;
class ZBottomBar;
class ZMessagePane;
class ZUserButton;

class HLine;
class VLine;

class MainWindow : public QMainWindow, public MainView {
        Q_OBJECT

    public:
        explicit MainWindow(const UserService &userService,
                            QWidget *parent = 0);
        ~MainWindow();

        virtual void addUser(UserRef userRef) override;
        virtual void deleteUser(UserRef userRef) override;

        virtual MessageRepositoryRef messageRepository() const override;

        virtual void
        setMessageRepository(MessageRepositoryRef messageRepo) override;

        virtual void
        setMessageHandler(std::function<void(std::string)> handler) override;

        virtual void clearMessageText() override;

    private:
        const UserService &m_UserService;
        MessageRepositoryRef m_ActiveRepo;

        ChatView *m_ChatView;
};
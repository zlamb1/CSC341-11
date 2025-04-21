#pragma once

#include <QWidget>
#include <functional>

#include "data/msgrepo.hpp"
#include "data/user.hpp"
#include "service/userservice.hpp"
#include "ui/mainview.hpp"

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

class MainWidget : public QWidget, public MainView {
        Q_OBJECT

    public:
        explicit MainWidget(const UserService &userService,
                            QWidget *parent = 0);
        ~MainWidget();

        virtual void addUser(UserRef userRef) override;
        virtual void deleteUser(UserRef userRef) override;

        virtual MessageRepositoryRef messageRepository() const override;

        virtual void
        setMessageRepository(MessageRepositoryRef messageRepo) override;

        virtual void
        setMessageHandler(std::function<void(std::string)> handler) override;

        virtual void clearMessageText() override;

    private:
        MessageRepositoryRef m_ActiveRepo;

        std::function<void(std::string)> m_MessageHandler = NULL;

        QGridLayout *m_Layout;

        QScrollArea *m_MessagePaneScrollArea;
        ZMessagePane *m_MessagePane;

        VLine *m_SideSeparator;
        HLine *m_BottomSeparator;

        ZSideBar *m_SideBar;
        ZBottomBar *m_BottomBar;
};
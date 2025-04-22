#pragma once

#include <QWidget>

#include "data/msgrepo.hpp"
#include "data/user.hpp"
#include "service/userservice.hpp"

class QGridLayout;
class QScrollArea;

class HLine;
class VLine;

class ZBottomBar;
class ZMessagePane;
class ZSideBar;

class ChatView : public QWidget {
    public:
        explicit ChatView(const UserService &userService, QWidget *parent = 0);
        ~ChatView();

    signals:
        void addUser(UserRef userRef);
        void deleteUser(UserRef userRef);

        void setMessageRepository(IMessageRepositoryRef messageRepo);
        void setMessageHandler(std::function<void(std::string)> messageHandler);
        void clearMessageText();

    protected:
        QGridLayout *m_Layout;

        QScrollArea *m_MessagePaneScrollArea;
        ZMessagePane *m_MessagePane;

        VLine *m_SideSeparator;
        HLine *m_BottomSeparator;

        ZSideBar *m_SideBar;
        ZBottomBar *m_BottomBar;

        std::function<void(std::string)> m_MessageHandler;
};
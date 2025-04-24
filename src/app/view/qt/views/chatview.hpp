#pragma once

#include <QWidget>

#include "data/msgrepo.hpp"
#include "data/user.hpp"

class QLabel;
class QGridLayout;
class QScrollArea;

class HLine;
class VLine;

class ZBottomBar;
class ZMessagePane;
class ZSideBar;

class ChatView : public QWidget {
        Q_OBJECT
    public:
        explicit ChatView(QWidget *parent = 0);

        void setChat(UserRef userRef);

        void addUser(UserRef userRef);
        void deleteUser(UserRef userRef);

        void setMessageRepository(IMessageRepositoryRef messageRepo);
        void clearMessageText();

        void
        setOpenChatHandler(std::function<void(std::string)> openChatHandler);

    signals:
        void messageSent(std::string text);

    protected:
        QGridLayout *m_Layout;

        QLabel *m_TopLabel;

        QScrollArea *m_MessagePaneScrollArea;
        ZMessagePane *m_MessagePane;

        VLine *m_SideSeparator;
        HLine *m_BottomSeparator;

        ZSideBar *m_SideBar;
        ZBottomBar *m_BottomBar;
};
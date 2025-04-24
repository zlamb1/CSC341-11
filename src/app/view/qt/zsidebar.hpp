#pragma once

#include <unordered_map>

#include "data/user.hpp"
#include "zuserbutton.hpp"

class QLabel;
class QPaintEvent;
class QVBoxLayout;

class ZSideBar : public QWidget {
        Q_OBJECT
    public:
        explicit ZSideBar(QWidget *parent = 0);

        void setChat(UserRef userRef);

        void addUser(UserRef userRef);
        void deleteUser(UserRef userRef);
        void clearUsers();

        void
        setOpenChatHandler(std::function<void(std::string)> openChatHandler);

    protected:
        void updateMemberCount(int newCount);

    private:
        QVBoxLayout *m_Layout;
        QLabel *m_MembersLabel;

        std::unordered_map<std::string, ZUserButton *> m_UserButtons;

        int m_MemberCount = 0;

        std::function<void(std::string)> m_OpenChatHandler;
};
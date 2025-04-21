#pragma once

#include <unordered_map>

#include "data/user.hpp"
#include "service/userservice.hpp"
#include "zuserbutton.hpp"

class QLabel;
class QPaintEvent;
class QVBoxLayout;

class ZSideBar : public QWidget {
        Q_OBJECT
    public:
        explicit ZSideBar(const UserService &userService, QWidget *parent = 0);
        ~ZSideBar();

        void addUser(UserRef userRef);
        void deleteUser(UserRef userRef);

    protected:
        void updateMemberCount(int newCount);

    private:
        QVBoxLayout *m_Layout;
        QLabel *m_MembersLabel;

        std::unordered_map<std::string, ZUserButton *> m_UserButtons;

        int m_MemberCount = 0;
};
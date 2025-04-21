#include <QGridLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>

#include "data/user.hpp"
#include "widgets/mainwidget.hpp"
#include "widgets/zsidebar.hpp"
#include "widgets/zuserbutton.hpp"

ZSideBar::ZSideBar(const UserService &userService, QWidget *parent)
    : QWidget(parent) {
    m_Layout = new QVBoxLayout();
    m_Layout->setAlignment(Qt::AlignTop);

    m_MembersLabel = new QLabel();
    m_Layout->addWidget(m_MembersLabel);

    auto users = userService.users();
    for (auto user : users)
        addUser(user);

    setLayout(m_Layout);
}

ZSideBar::~ZSideBar() {
    delete m_MembersLabel;
    delete m_Layout;
}

void ZSideBar::addUser(UserRef userRef) {
    auto *button = new ZUserButton(userRef);
    m_UserButtons[userRef->name()] = button;
    updateMemberCount(m_MemberCount + 1);
    m_Layout->addWidget(button);
}

void ZSideBar::deleteUser(UserRef userRef) {
    if (m_UserButtons.count(userRef->name())) {
        auto *button = m_UserButtons[userRef->name()];
        m_UserButtons.erase(userRef->name());
        updateMemberCount(m_MemberCount - 1);
        m_Layout->removeWidget(button);
    }
}

void ZSideBar::updateMemberCount(int newCount) {
    m_MemberCount = newCount;
    m_MembersLabel->setText("Members—1");
}
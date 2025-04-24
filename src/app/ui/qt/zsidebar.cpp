#include <QGridLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>

#include "data/user.hpp"
#include "zsidebar.hpp"
#include "zuserbutton.hpp"

ZSideBar::ZSideBar(QWidget *parent) : QWidget(parent) {
    m_Layout = new QVBoxLayout();
    m_Layout->setAlignment(Qt::AlignTop);

    m_MembersLabel = new QLabel();
    m_Layout->addWidget(m_MembersLabel);

    updateMemberCount(0);

    setLayout(m_Layout);
}

ZSideBar::~ZSideBar() {
    delete m_MembersLabel;
    delete m_Layout;
}

void ZSideBar::addUser(UserRef userRef) {
    auto *button                   = new ZUserButton(userRef);
    m_UserButtons[userRef->name()] = button;
    m_Layout->addWidget(button);
    updateMemberCount(m_MemberCount + 1);
}

void ZSideBar::deleteUser(UserRef userRef) {
    if (m_UserButtons.count(userRef->name())) {
        auto button = m_UserButtons[userRef->name()];
        m_UserButtons.erase(userRef->name());
        m_Layout->removeWidget(button);
        button->deleteLater();
        updateMemberCount(m_MemberCount - 1);
    }
}

void ZSideBar::clearUsers() {
    for (auto pair : m_UserButtons) {
        m_Layout->removeWidget(pair.second);
        pair.second->deleteLater();
    }
    m_UserButtons.clear();
    updateMemberCount(0);
}

void ZSideBar::updateMemberCount(int newCount) {
    m_MemberCount  = newCount;
    auto labelText = QString("Members—%1").arg(m_MemberCount);
    m_MembersLabel->setText(labelText);
}
#include <QGridLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <functional>
#include <qpushbutton.h>

#include "data/user.hpp"
#include "zsidebar.hpp"
#include "zuserbutton.hpp"

ZSideBar::ZSideBar(QWidget *parent) : QWidget(parent) {
    m_Layout = new QVBoxLayout(this);
    m_Layout->setAlignment(Qt::AlignTop);

    m_MembersLabel = new QLabel(this);
    m_Layout->addWidget(m_MembersLabel);

    updateMemberCount(0);

    setLayout(m_Layout);
}

void ZSideBar::setChat(UserRef userRef) {
    if (m_UserButtons.count(userRef->name())) {
        m_UserButtons[userRef->name()]->setSelected(true);
    }
}

void ZSideBar::addUser(UserRef userRef) {
    auto *button = new ZUserButton(userRef, this);

    if (m_OpenChatHandler)
        button->setClickHandler(m_OpenChatHandler);

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

void ZSideBar::setOpenChatHandler(
    std::function<void(std::string)> openChatHandler) {
    for (auto pair : m_UserButtons) {
        auto button = pair.second;
        button->setClickHandler(openChatHandler);
    }
    m_OpenChatHandler = openChatHandler;
}
#include <QGridLayout>
#include <QPainter>
#include <QPushButton>
#include <qnamespace.h>
#include <qobject.h>
#include <qstyle.h>

#include "data/user.hpp"
#include "zuserbutton.hpp"

ZUserButton::ZUserButton(UserRef userRef, QWidget *parent)
    : QWidget(parent), m_UserRef(userRef) {
    m_Layout = new QGridLayout(this);

    m_Button = new QPushButton(userRef->name().c_str(), this);
    m_Button->setMinimumHeight(20);
    m_Button->setStyleSheet(
        QString("background-color: transparent; border: 0;"));
    m_Button->setFlat(true);

    m_Layout->addWidget(m_Button);

    setCursor(Qt::OpenHandCursor);
    setLayout(m_Layout);
}

void ZUserButton::paintEvent(QPaintEvent *event) {
    if (m_Hovering) {
        QPainter painter(this);
        painter.setPen(Qt::transparent);
        painter.setBrush(m_HoverColor);
        painter.drawRoundedRect(0, 0, width(), height(), 5, 5);
    }
    QWidget::paintEvent(event);
}

void ZUserButton::enterEvent(QEnterEvent *event) {
    m_Hovering = true;
    update();
    QWidget::enterEvent(event);
}

void ZUserButton::leaveEvent(QEvent *event) {
    m_Hovering = false;
    update();
    QWidget::leaveEvent(event);
}
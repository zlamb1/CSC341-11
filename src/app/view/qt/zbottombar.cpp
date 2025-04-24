#include <QColor>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

#include "zbottombar.hpp"

ZBottomBar::ZBottomBar(QWidget *parent) : QWidget(parent) {
    m_MsgLineEdit = new QLineEdit(this);
    m_MsgLineEdit->setPlaceholderText("Enter Message");
    m_MsgLineEdit->setFixedHeight(40);

    m_SubmitBtn = new QPushButton("Submit", this);
    m_SubmitBtn->setFixedHeight(40);

    QObject::connect(m_SubmitBtn, &QPushButton::clicked, [&]() {
        sendMessage(m_MsgLineEdit->text().toStdString());
    });

    auto layout = new QGridLayout(this);

    layout->addWidget(m_MsgLineEdit, 0, 0, 1, 1);
    layout->addWidget(m_SubmitBtn, 0, 1, 1, 1);

    setLayout(layout);
}

void ZBottomBar::clearMessageText() {
    m_MsgLineEdit->clear();
}

void ZBottomBar::sendMessage(std::string text) {
    if (!text.empty()) {
        emit messageSent(text);
    }
}
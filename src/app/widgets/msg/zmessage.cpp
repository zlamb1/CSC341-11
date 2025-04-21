#include <QVBoxLayout>
#include <qlabel.h>

#include "widgets/msg/zmessage.hpp"

ZMessage::ZMessage(MessageRef messageRef, QWidget *parent)
    : QWidget(parent), m_Message(messageRef) {
    m_Layout = new QVBoxLayout;

    m_UserLabel = new QLabel(messageRef->sender()->name().c_str());
    m_Layout->addWidget(m_UserLabel);

    m_MessageLabel = new QLabel(messageRef->text().c_str());
    m_Layout->addWidget(m_MessageLabel);

    setLayout(m_Layout);
}

ZMessage::~ZMessage() {
    delete m_UserLabel;
    delete m_MessageLabel;
    delete m_Layout;
}
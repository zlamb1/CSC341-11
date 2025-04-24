#include <QGridLayout>
#include <QPushButton>
#include <qglobal.h>

#include "menuview.hpp"

MenuView::MenuView(QWidget *parent) : QWidget(parent) {
    m_Layout = new QGridLayout;

    m_HostButton = new QPushButton("Host");
    QObject::connect(m_HostButton, &QPushButton::clicked, this,
                     &MenuView::onHost);

    m_ConnectButton = new QPushButton("Connect");
    QObject::connect(m_ConnectButton, &QPushButton::clicked, this,
                     &MenuView::onConnect);

    m_Layout->addWidget(m_HostButton);
    m_Layout->addWidget(m_ConnectButton);

    setLayout(m_Layout);
}

MenuView::~MenuView() {
    delete m_HostButton;
    delete m_ConnectButton;
    delete m_Layout;
}
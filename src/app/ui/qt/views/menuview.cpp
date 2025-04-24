#include <QComboBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QNetworkInterface>
#include <QPushButton>
#include <qcombobox.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qhostaddress.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qregularexpression.h>
#include <qvalidator.h>

#include "menuview.hpp"

MenuView::MenuView(QWidget *parent) : QWidget(parent) {
    m_Layout              = new QGridLayout(this);
    m_HostButtonLayout    = new QGridLayout;
    m_ConnectButtonLayout = new QGridLayout;

    m_PortValidator = new QRegularExpressionValidator(this);
    m_PortValidator->setRegularExpression(QRegularExpression("^[0-9]{0,5}$"));

    m_AddressValidator = new QRegularExpressionValidator(this);
    m_AddressValidator->setRegularExpression(
        QRegularExpression("^([0-9]{1,3}\\.){3}[0-9]{1,3}$"));

    m_HostLayout    = new QFormLayout;
    m_ConnectLayout = new QFormLayout;

    m_HostContainer    = new QWidget(this);
    m_ConnectContainer = new QWidget(this);

    m_HostAddressCombo = new QComboBox(this);

    QString ipAddress;
    const QList<QHostAddress> ipAddressesList =
        QNetworkInterface::allAddresses();

    for (const QHostAddress &entry : ipAddressesList) {
        if (entry.toIPv4Address()) {
            m_HostAddressCombo->addItem(entry.toString());
        }
    }

    m_ConnectAddress  = new QLineEdit(this);
    m_HostPortEdit    = new QLineEdit(this);
    m_ConnectPortEdit = new QLineEdit(this);

    m_HostPortEdit->setText("9090");
    m_HostPortEdit->setValidator(m_PortValidator);

    m_ConnectPortEdit->setText("9090");
    m_ConnectPortEdit->setValidator(m_PortValidator);

    m_ConnectAddress->setText("127.0.0.1");
    m_ConnectAddress->setValidator(m_AddressValidator);

    m_HostLayout->addRow(tr("Host Address"), m_HostAddressCombo);
    m_HostLayout->addRow(tr("Host Port"), m_HostPortEdit);

    m_ConnectLayout->addRow(tr("Connect Address"), m_ConnectAddress);
    m_ConnectLayout->addRow(tr("Connect Port"), m_ConnectPortEdit);

    m_HostButton = new QPushButton("Host", this);
    QObject::connect(m_HostButton, &QPushButton::clicked, this, [this] {
        emit onHost(m_HostAddressCombo->currentText().toStdString(),
                    m_HostPortEdit->text().toUInt());
    });

    m_ConnectButton = new QPushButton("Connect", this);
    QObject::connect(m_ConnectButton, &QPushButton::clicked, this, [this] {
        emit onConnect(m_ConnectAddress->text().toStdString(),
                       m_ConnectPortEdit->text().toUInt());
    });

    m_HostButtonLayout->addWidget(m_HostButton);
    m_HostLayout->addRow(m_HostButtonLayout);

    m_ConnectButtonLayout->addWidget(m_ConnectButton);
    m_ConnectLayout->addRow(m_ConnectButtonLayout);

    m_HostContainer->setLayout(m_HostLayout);
    m_ConnectContainer->setLayout(m_ConnectLayout);

    m_Layout->addWidget(m_HostContainer);
    m_Layout->addWidget(m_ConnectContainer);
}
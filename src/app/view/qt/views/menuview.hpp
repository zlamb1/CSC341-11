#pragma once

#include <QWidget>
#include <qvalidator.h>

class QLineEdit;
class QGridLayout;
class QPushButton;
class QComboBox;
class QFormLayout;

class MenuView : public QWidget {
        Q_OBJECT
    public:
        explicit MenuView(QWidget *parent = nullptr);

    signals:
        void onHost(std::string hostAddress, uint16_t port);
        void onConnect(std::string hostAddress, uint16_t port);

    protected:
        QGridLayout *m_Layout, *m_HostButtonLayout, *m_ConnectButtonLayout;
        QFormLayout *m_HostLayout, *m_ConnectLayout;
        QWidget *m_HostContainer, *m_ConnectContainer;
        QComboBox *m_HostAddressCombo;
        QLineEdit *m_ConnectAddress, *m_HostPortEdit, *m_ConnectPortEdit;
        QRegularExpressionValidator *m_PortValidator, *m_AddressValidator;
        QPushButton *m_HostButton, *m_ConnectButton;
};
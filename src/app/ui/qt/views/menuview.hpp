#pragma once

#include <QWidget>

class QGridLayout;
class QPushButton;

class MenuView : public QWidget {
        Q_OBJECT
    public:
        explicit MenuView(QWidget *parent = nullptr);
        ~MenuView();

    signals:
        void onHost();
        void onConnect();

    protected:
        QGridLayout *m_Layout;

        QPushButton *m_HostButton, *m_ConnectButton;
};
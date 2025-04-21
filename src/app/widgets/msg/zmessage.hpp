#pragma once

#include <QWidget>

#include "data/msg.hpp"

class QVBoxLayout;
class QLabel;

class ZMessage : public QWidget {
        Q_OBJECT
    public:
        explicit ZMessage(MessageRef messageRef, QWidget *parent = 0);
        ~ZMessage();

    protected:
        MessageRef m_Message;

        QVBoxLayout *m_Layout;
        QLabel *m_UserLabel, *m_MessageLabel;

    private:
};
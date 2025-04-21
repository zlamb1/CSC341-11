#pragma once

#include <QEnterEvent>
#include <QPaintEvent>
#include <QWidget>

#include "data/user.hpp"

class QPushButton;

class ZUserButton : public QWidget {
        Q_OBJECT
    public:
        explicit ZUserButton(UserRef userRef, QWidget *parent = 0);
        ~ZUserButton();

    protected:
        UserWeakRef m_UserRef;
        QPushButton *m_Button;

        bool m_Hovering = false;
        QColor m_HoverColor = QColor(255, 255, 255, 20);

        void paintEvent(QPaintEvent *event);

        void enterEvent(QEnterEvent *event);
        void leaveEvent(QEvent *event);

    private:
};
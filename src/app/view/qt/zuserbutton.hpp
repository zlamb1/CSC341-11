#pragma once

#include <QEnterEvent>
#include <QPaintEvent>
#include <QWidget>
#include <qobjectdefs.h>

#include "data/user.hpp"

class QGridLayout;
class QPushButton;

class ZUserButton : public QWidget {
        Q_OBJECT
    public:
        explicit ZUserButton(UserRef userRef, QWidget *parent = 0);

        bool hovering() const;
        bool selected() const;

        void setSelected(bool selected);

        void setClickHandler(std::function<void(std::string)> clickHandler);
        bool removeClickHandler();

    protected:
        UserWeakRef m_UserRef;

        QGridLayout *m_Layout;
        QPushButton *m_Button;

        bool m_HasConnection = false;
        QMetaObject::Connection m_Connection;

        bool m_Hovering = false;
        bool m_Selected = false;

        QColor m_HoverColor = QColor(255, 255, 255, 20);

        void paintEvent(QPaintEvent *event);

        void enterEvent(QEnterEvent *event);
        void leaveEvent(QEvent *event);

    private:
};
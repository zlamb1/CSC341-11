#pragma once

#include <QFrame>

class HLine : public QFrame {
        Q_OBJECT
    public:
        explicit HLine(QWidget *parent = 0);

        QColor color() const;
        void setColor(QColor color);

    protected:
        QColor m_Color;

    private:
};
#pragma once

#include <QFrame>

class VLine : public QFrame {
        Q_OBJECT
    public:
        explicit VLine(QWidget *parent = 0);
        ~VLine(){};

        QColor color() const;
        void setColor(QColor color);

    protected:
        QColor m_Color;

    private:
};
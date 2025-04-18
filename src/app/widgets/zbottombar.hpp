#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;

class ZBottomBar : public QWidget {
        Q_OBJECT

    public:
        explicit ZBottomBar(QWidget *parent = 0);
        ~ZBottomBar();

    private:
        QLineEdit *msgLineEditor;
        QLineEdit *userLineEditor;

        QPushButton *submitBtn;
};
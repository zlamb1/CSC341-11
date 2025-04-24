#pragma once

#include <QWidget>

class QLabel;
class QLineEdit;
class QPaintEvent;
class QPushButton;

class ZBottomBar : public QWidget {
        Q_OBJECT

    public:
        explicit ZBottomBar(QWidget *parent = 0);

        void clearMessageText();

    protected slots:
        void sendMessage(std::string text);

    signals:
        void messageSent(std::string text);

    private:
        QLineEdit *m_MsgLineEdit;
        QPushButton *m_SubmitBtn;
};
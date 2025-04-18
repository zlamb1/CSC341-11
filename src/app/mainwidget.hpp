#pragma once

#include <QWidget>

class QLineEdit; 

namespace UI {
    class MainWidget; 
}

class MainWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    QLineEdit *lineEditor;

};
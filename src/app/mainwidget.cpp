#include <QtWidgets>

#include <QLineEdit>
#include <qlineedit.h>

#include "mainwidget.hpp"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    auto *layout = new QGridLayout();

    lineEditor = new QLineEdit();

    layout->addWidget(lineEditor, 0, 0, 1, 1);

    setLayout(layout);
    setWindowTitle(tr("EmberChat"));
}

MainWidget::~MainWidget() { delete lineEditor; }
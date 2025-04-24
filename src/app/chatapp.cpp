#include <QApplication>

#include "chatapp.hpp"
#include "model/chatmodel.hpp"
#include "view/qt/mainwindow.hpp"

ChatApp::ChatApp(int argc, char *argv[]) {
    QApplication app(argc, argv);

    srand(time(0));

    m_AppModel = new ChatAppModel;
    m_AppView  = new MainWindow(m_AppModel);
    m_AppView->show();

    app.exec();
}

ChatApp::~ChatApp() {
    delete m_AppView;
    delete m_AppModel;
}
#pragma once

#include <QMainWindow>

#include "data/msgrepo.hpp"
#include "model/appmodel.hpp"
#include "view/appview.h"
#include "views/chatview.hpp"
#include "views/menuview.hpp"

class QGridLayout;
class QLabel;
class QLineEdit;
class QScrollArea;
class QStackedWidget;

class ZSideBar;
class ZBottomBar;
class ZMessagePane;
class ZUserButton;

class HLine;
class VLine;

class MainWindow : public QMainWindow, public IAppView {
        Q_OBJECT

    public:
        explicit MainWindow(IAppModel *appModel, QWidget *parent = 0);
        virtual ~MainWindow() = default;

        virtual void show() override;

    private:
        QStackedWidget *m_CenterWidget;

        MenuView *m_MenuView;
        ChatView *m_ChatView;

        IMessageRepositoryRef m_ActiveRepo;

        bool m_HostHandlerSet = false, m_ConnectHandlerSet = false;
        QMetaObject::Connection m_HostHandler, m_ConnectHandler;
};
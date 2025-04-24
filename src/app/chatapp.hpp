#pragma once

#include "view/appview.h"

class ChatApp {

    public:
        ChatApp(int argc, char *argv[]);
        ~ChatApp();

    protected:
        IAppModel *m_AppModel;
        IAppView *m_AppView;
};
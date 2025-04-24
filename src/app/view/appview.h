#pragma once

#include "model/appmodel.hpp"

class IAppView {
    public:
        IAppView(IAppModel *appModel) : m_AppModel(appModel){};
        virtual ~IAppView() = default;

        virtual void show() = 0;

    protected:
        IAppModel *m_AppModel;
};
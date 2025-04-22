#pragma once

#include <QWidget>

#include "data/msgrepo.hpp"

class QLabel;
class QVBoxLayout;

class ZMessagePane : public QWidget {
        Q_OBJECT
    public:
        explicit ZMessagePane(QWidget *parent = 0);

        IMessageRepositoryRef messageRepository() const;
        void setMessageRepository(IMessageRepositoryRef messageRepository);

        void clearMessages();

    protected:
        QVBoxLayout *m_Layout;

        IMessageRepositoryRef m_MessageRepo;

        HandlerRef<MessageEvent> m_MessageAddHandler;

        void addMessage(MessageRef message);

    private:
        void onMessage(MessageEvent &event);
};
#pragma once

#include <memory>
#include <vector>

#include "data/msg.hpp"
#include "event/handler.hpp"
#include "event/msgevent.hpp"

enum class RepositoryType : int { GLOBAL, DIRECT, GROUP };

class IMessageRepository {
    public:
        virtual RepositoryType repositoryType() const           = 0;
        virtual const std::vector<MessageRef> &messages() const = 0;

        virtual void createMessage(std::string text, UserRef sender) = 0;
        virtual void createMessage(std::string text, UserRef sender,
                                   MessageTime messageTime)          = 0;

        virtual void
        addMessageAddHandler(HandlerRef<MessageEvent> messageAddHandler) = 0;

        virtual bool
        removeMessageAddHandler(HandlerRef<MessageEvent> messageAddHandler) = 0;
};

class MessageRepository : public IMessageRepository {
    public:
        MessageRepository(RepositoryType repositoryType)
            : m_RepoType(repositoryType) {}

        RepositoryType repositoryType() const override {
            return m_RepoType;
        }

        const std::vector<MessageRef> &messages() const override {
            return m_Messages;
        }

        virtual void createMessage(std::string text, UserRef sender) override {
            MessageRef messageRef = std::make_shared<Message>(text, sender);
            addMessage(messageRef);
        }

        virtual void createMessage(std::string text, UserRef sender,
                                   MessageTime messageTime) override {
            MessageRef messageRef =
                std::make_shared<Message>(text, sender, messageTime);
            addMessage(messageRef);
        }

        void addMessage(MessageRef messageRef) {
            m_Messages.emplace_back(messageRef);
            MessageEvent messageEvent(messageRef);
            for (auto iter = m_MessageAddHandlers.begin();
                 iter != m_MessageAddHandlers.end();) {
                auto handlerRef = iter->lock();
                if (!handlerRef) {
                    iter = m_MessageAddHandlers.erase(iter);
                } else {
                    handlerRef->onEvent(messageEvent);
                    iter++;
                }
            }
        }

        void addMessageAddHandler(
            HandlerRef<MessageEvent> messageAddHandler) override {
            m_MessageAddHandlers.emplace_back(messageAddHandler);
        }

        bool removeMessageAddHandler(
            HandlerRef<MessageEvent> messageAddHandler) override {
            for (auto iter = m_MessageAddHandlers.begin();
                 iter != m_MessageAddHandlers.end();) {
                auto handlerRef = iter->lock();
                if (!handlerRef) {
                    iter = m_MessageAddHandlers.erase(iter);
                } else if (handlerRef == messageAddHandler) {
                    m_MessageAddHandlers.erase(iter);
                    return true;
                } else
                    iter++;
            }
            return false;
        }

    protected:
        RepositoryType m_RepoType;
        std::vector<MessageRef> m_Messages;
        HandlerList<MessageEvent> m_MessageAddHandlers;

    private:
};

using IMessageRepositoryRef = std::shared_ptr<IMessageRepository>;
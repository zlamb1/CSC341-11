#pragma once

#include <memory>
#include <vector>

#include "data/msg.hpp"
#include "event/handler.hpp"
#include "event/msg_event.hpp"

enum class RepositoryType : int { GLOBAL, DIRECT, GROUP };

class MessageRepository {
    public:
        MessageRepository(RepositoryType repositoryType)
            : m_RepoType(repositoryType) {}

        RepositoryType repositoryType() const {
            return m_RepoType;
        }

        const std::vector<MessageRef> &messages() const {
            return m_Messages;
        }

        void createMessage(std::string text, UserRef sender) {
            MessageRef messageRef = std::make_shared<Message>(text, sender);
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

        void addMessageAddHandler(HandlerRef<MessageEvent> messageAddHandler) {
            m_MessageAddHandlers.emplace_back(messageAddHandler);
        }

        bool
        removeMessageAddHandler(HandlerRef<MessageEvent> messageAddHandler) {
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

using MessageRepositoryRef = std::shared_ptr<MessageRepository>;
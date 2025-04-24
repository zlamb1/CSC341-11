#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include "data/msgrepo.hpp"

template <typename ReturnType = void, typename... Args>
using Function = std::function<ReturnType(Args...)>;

class IAppModel {
    public:
        virtual ~IAppModel() = default;

        IMessageRepositoryRef activeMessageRepository();
        void setActiveMessageRepository(
            IMessageRepositoryRef activeMessageRepository);

        const std::string &requestedName() const;
        void setRequestedName(std::string requestedName);

        virtual void sendMessage(std::string text) = 0;

        virtual void connectToHost(std::string hostAddress, uint16_t port) = 0;
        virtual void hostServer(std::string hostAddress, uint16_t port)    = 0;

        void notifyUserAddNotifier(Function<void, UserRef> userAddNotifier);
        void
        notifyUserDeleteNotifier(Function<void, UserRef> userDeleteNotifier);

        void
        notifyMessageAddNotifier(Function<void, MessageRef> messageAddNotifier);

        void notifyActiveMessageRepositoryChange(
            Function<void, IMessageRepositoryRef>
                activeMessageRepositoryNotifier);

        void notifyClientConnectNotifier(Function<void> clientConnectNotifier);
        void
        notifyClientDisconnectNotifier(Function<void> clientDisconnectNotifier);

    protected:
        IMessageRepositoryRef m_ActiveMessageRepository;
        std::string m_RequestedName;

        Function<void, UserRef> m_UserAddNotifier;
        Function<void, UserRef> m_UserDeleteNotifier;

        Function<void, MessageRef> m_MessageAddNotifier;

        Function<void, IMessageRepositoryRef> m_ActiveMessageRepositoryNotifier;

        Function<void> m_ClientConnectNotifier;
        Function<void> m_ClientDisconnectNotifier;
};
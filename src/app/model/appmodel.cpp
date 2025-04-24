#include "appmodel.hpp"
#include "data/user.hpp"
#include "service/userservice.hpp"

IUserServiceRef IAppModel::activeUserService() const {
    return m_ActiveUserService;
}

void IAppModel::setActiveUserService(IUserServiceRef activeUserService) {
    m_ActiveUserService = activeUserService;
}

IMessageRepositoryRef IAppModel::activeMessageRepository() const {
    return m_ActiveMessageRepository;
}

void IAppModel::setActiveMessageRepository(
    IMessageRepositoryRef activeMessageRepository) {
    m_ActiveMessageRepository = activeMessageRepository;
    if (m_ActiveMessageRepositoryNotifier)
        m_ActiveMessageRepositoryNotifier(m_ActiveMessageRepository);
}

const std::string &IAppModel::requestedName() const {
    return m_RequestedName;
}

void IAppModel::setRequestedName(std::string requestedName) {
    m_RequestedName = requestedName;
}

void IAppModel::notifyUserAddNotifier(Function<void, UserRef> userAddNotifier) {
    m_UserAddNotifier = userAddNotifier;
}

void IAppModel::notifyUserDeleteNotifier(
    Function<void, UserRef> userDeleteNotifier) {
    m_UserDeleteNotifier = userDeleteNotifier;
}

void IAppModel::notifyMessageAddNotifier(
    Function<void, MessageRef> messageAddHandler) {
    m_MessageAddNotifier = messageAddHandler;
}

void IAppModel::notifyActiveMessageRepositoryChange(
    Function<void, IMessageRepositoryRef> activeMessageRepositoryNotifier) {
    m_ActiveMessageRepositoryNotifier = activeMessageRepositoryNotifier;
}

void IAppModel::notifyClientConnectNotifier(
    Function<void> clientConnectNotifier) {
    m_ClientConnectNotifier = clientConnectNotifier;
}

void IAppModel::notifyClientDisconnectNotifier(
    Function<> clientDisconnectNotifier) {
    m_ClientDisconnectNotifier = clientDisconnectNotifier;
}
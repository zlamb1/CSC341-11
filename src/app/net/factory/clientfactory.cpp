#include "clientfactory.hpp"
#include "net/client/msgrepo.hpp"
#include "net/client/userservice.hpp"
#include <memory>

INetworkServiceRef ClientNetworkFactory::createNetworkService() {
    // FIXME:
    return nullptr;
}

IUserServiceRef
ClientNetworkFactory::createUserService(IUserServiceRef wrappedUserService,
                                        INetworkServiceRef networkService) {
    return std::make_shared<ClientUserService>(wrappedUserService,
                                               networkService);
}

IMessageRepositoryRef ClientNetworkFactory::createNetworkMessageRepository(
    IMessageRepositoryRef wrappedMessageRepo,
    INetworkServiceRef networkService) {
    return std::make_shared<ClientMessageRepository>(wrappedMessageRepo,
                                                     networkService);
}
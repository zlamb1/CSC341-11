#pragma once

#include "net/factory/networkfactory.hpp"
#include "net/networkservice.hpp"

class ClientNetworkFactory : public IAbstractNetworkFactory {
    public:
        virtual INetworkServiceRef createNetworkService() override;
        virtual IUserServiceRef
        createUserService(IUserServiceRef wrappedUserService,
                          INetworkServiceRef networkService) override;
        virtual IMessageRepositoryRef createNetworkMessageRepository(
            IMessageRepositoryRef wrappedMessageRepo,
            INetworkServiceRef networkService) override;
};
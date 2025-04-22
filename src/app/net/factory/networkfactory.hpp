#pragma once

#include "data/msgrepo.hpp"
#include "net/networkservice.hpp"
#include "service/userservice.hpp"

class IAbstractNetworkFactory {
    public:
        virtual INetworkServiceRef createNetworkService() = 0;
        virtual IUserServiceRef
        createUserService(IUserServiceRef wrappedUserService,
                          INetworkServiceRef networkService) = 0;
        virtual IMessageRepositoryRef
        createNetworkMessageRepository(IMessageRepositoryRef wrappedMessageRepo,
                                       INetworkServiceRef networkService) = 0;
};
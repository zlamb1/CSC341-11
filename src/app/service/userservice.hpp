#pragma once

#include <unordered_map>
#include <vector>

#include "data/user.hpp"
#include "event/handler.hpp"
#include "event/userevent.hpp"

enum class UserCreateResult : int { SUCCESS = 1, UNIQUE_NAME_REQIRED = -1 };

class UserService {
    public:
        UserService();

        UserRef activeUser();

        UserRef user(const std::string &name);
        const std::vector<UserRef> &users() const;

        UserCreateResult createUser(const std::string &name);

        void addUserAddHandler(HandlerRef<UserEvent> userAddHandler);
        bool removeUserAddHandler(HandlerRef<UserEvent> userAddHandler);

        void addUserDeleteHandler(HandlerRef<UserEvent> userDeleteHandler);
        bool removeUserDeleteHandler(HandlerRef<UserEvent> userDeleteHandler);

    protected:
        UserRef m_ActiveUser;

        std::vector<UserRef> m_Users;
        std::unordered_map<std::string, UserRef> m_UserMap;

        HandlerList<UserEvent> m_UserAddHandlers;
        HandlerList<UserEvent> m_UserDeleteHandlers;
};
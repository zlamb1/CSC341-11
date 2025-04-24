#pragma once

#include <unordered_map>
#include <vector>

#include "data/user.hpp"
#include "event/handler.hpp"
#include "event/userevent.hpp"

enum class UserCreateResult : int { SUCCESS = 1, UNIQUE_NAME_REQIRED = -1 };

class IUserService {
    public:
        virtual UserRef activeUser()                   = 0;
        virtual void setActiveUser(UserRef activeUser) = 0;

        virtual UserRef user(const std::string &name) = 0;

        virtual const std::vector<UserRef> &users() const = 0;

        virtual UserCreateResult createUser(const std::string &name) = 0;
        virtual bool deleteUser(const std::string &name)             = 0;

        virtual void
        addUserAddHandler(HandlerRef<UserEvent> userAddHandler) = 0;
        virtual bool
        removeUserAddHandler(HandlerRef<UserEvent> userAddHandler) = 0;

        virtual void
        addUserDeleteHandler(HandlerRef<UserEvent> userDeleteHandler) = 0;
        virtual bool
        removeUserDeleteHandler(HandlerRef<UserEvent> userDeleteHandler) = 0;
};

class UserService : public IUserService {
    public:
        virtual ~UserService() = default;

        virtual UserRef activeUser() override;
        virtual void setActiveUser(UserRef activeUser) override;

        virtual UserRef user(const std::string &name) override;
        virtual const std::vector<UserRef> &users() const override;

        virtual UserCreateResult createUser(const std::string &name) override;
        virtual bool deleteUser(const std::string &name) override;

        virtual void
        addUserAddHandler(HandlerRef<UserEvent> userAddHandler) override;
        virtual bool
        removeUserAddHandler(HandlerRef<UserEvent> userAddHandler) override;

        virtual void
        addUserDeleteHandler(HandlerRef<UserEvent> userDeleteHandler) override;
        virtual bool removeUserDeleteHandler(
            HandlerRef<UserEvent> userDeleteHandler) override;

    protected:
        UserRef m_ActiveUser;

        std::vector<UserRef> m_Users;
        std::unordered_map<std::string, UserRef> m_UserMap;

        HandlerList<UserEvent> m_UserAddHandlers;
        HandlerList<UserEvent> m_UserDeleteHandlers;
};

using IUserServiceRef = std::shared_ptr<IUserService>;
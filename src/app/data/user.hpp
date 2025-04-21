#pragma once

#include <memory>
#include <string>

class User {
    public:
        User(const std::string &name);

        const std::string &name() const;
        void setName(const std::string &name);

    protected:
        std::string m_Name;

    private:
};

using UserRef = std::shared_ptr<User>;
using UserWeakRef = std::weak_ptr<User>;
//
// Created by Константин Беляков on 15.12.2024.
//

#ifndef BITOCEN_USER_H
#define BITOCEN_USER_H

#include <memory>
#include <string>
#include "fabric/BaseObjectBuilder.h"

namespace model {

    class User;
    using UserPtr = std::shared_ptr<User>;

    class User : public fabric::BaseObjectBuilder {
    public:
        User();

    private:
        // UserID UUID?
        std::string id_;

        // Login any string (format as telegram)
        std::string login_;

    };

}


#endif //BITOCEN_USER_H

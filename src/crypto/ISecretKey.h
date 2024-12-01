//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_ISECRETKEY_H
#define BITOCEN_ISECRETKEY_H

#include <memory>

namespace crypto {

    class ISecretKey;
    using ISecretKeyPtr = std::shared_ptr<ISecretKey>;

    class ISecretKey {
    public:
        virtual ~ISecretKey() = default;

        virtual const std::string get_string() const = 0;
    };

}

#endif //BITOCEN_ISECRETKEY_H

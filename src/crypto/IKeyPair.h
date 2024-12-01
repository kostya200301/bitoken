//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_IKEYPAIR_H
#define BITOCEN_IKEYPAIR_H

#include <memory>
#include <string>
#include <iostream>

#include "IPublicKey.h"
#include "ISecretKey.h"


namespace crypto {

    class IKeyPair;
    using IKeyPairPtr = std::shared_ptr<IKeyPair>;

    class IKeyPair {

    public:

        virtual ~IKeyPair() = default;

        virtual const IPublicKeyPtr get_pk() const = 0;

        virtual const ISecretKeyPtr get_sk() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IKeyPairPtr& keyPair) {
            os << "{Secret Key: [" << keyPair->get_sk()->get_string() << "], Public Key: [" << keyPair->get_pk()->get_string() << "]}";
            return os;
        }

    };

}




#endif //BITOCEN_IKEYPAIR_H

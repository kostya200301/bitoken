//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_IPUBLICKEY_H
#define BITOCEN_IPUBLICKEY_H

namespace crypto {

    class IPublicKey;
    using IPublicKeyPtr = std::shared_ptr<IPublicKey>;

    class IPublicKey {
    public:
        virtual ~IPublicKey() = default;

        virtual const std::string get_string() const = 0;
    };

}


#endif //BITOCEN_IPUBLICKEY_H

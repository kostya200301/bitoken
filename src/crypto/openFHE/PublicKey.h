//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_PUBLICKEY_H
#define BITOCEN_PUBLICKEY_H

#include <memory>
#include "openfhe.h"
#include "crypto/IPublicKey.h"


namespace crypto {

    class PublicKey;
    using PublicKeyPtr = std::shared_ptr<PublicKey>;

    class PublicKey : public IPublicKey {
    public:
        PublicKey(lbcrypto::PublicKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data);

        ~PublicKey() override;

        [[nodiscard]] const std::string get_string() const override;

        friend class CryptoContext;

    private:
        lbcrypto::PublicKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data_;
    };

}

#endif //BITOCEN_PUBLICKEY_H

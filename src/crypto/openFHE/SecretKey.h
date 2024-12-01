//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_SECRETKEY_H
#define BITOCEN_SECRETKEY_H

#include <memory>
#include "openfhe.h"
#include "crypto/ISecretKey.h"

namespace crypto {

    class SecretKey;
    using SecretKeyPtr = std::shared_ptr<SecretKey>;

    class SecretKey : public ISecretKey {
    public:
        SecretKey(lbcrypto::PrivateKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data);

        ~SecretKey() override;

        [[nodiscard]] const std::string get_string() const override;

        friend class CryptoContext;

    private:
        lbcrypto::PrivateKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data_;
    };

}


#endif //BITOCEN_SECRETKEY_H

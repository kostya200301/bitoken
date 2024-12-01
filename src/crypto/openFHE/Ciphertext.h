//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_CIPHERTEXT_H
#define BITOCEN_CIPHERTEXT_H

#include "crypto/ICiphertext.h"
#include "openfhe.h"

namespace crypto {

    class Ciphertext;
    using CiphertextPtr = std::shared_ptr<Ciphertext>;

    class Ciphertext : public ICiphertext {
    public:
        Ciphertext(lbcrypto::Ciphertext<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data_);

        ~Ciphertext() override;

        friend class CryptoContext;

    private:
        lbcrypto::Ciphertext<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data_;

    };

}


#endif //BITOCEN_CIPHERTEXT_H

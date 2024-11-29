//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_CRYPTOCONTEXT_H
#define BITOCEN_CRYPTOCONTEXT_H

#include "crypto/ICryptoContext.h"
#include "openfhe.h"
#include <cereal/archives/portable_binary.hpp>


namespace crypto {

    class CryptoContext : public ICryptoContext {
    public:
        CryptoContext();

        KeyPairPtr GenerateFHEKeyPair() override;

    private:
        lbcrypto::CryptoContext<lbcrypto::DCRTPoly> cc;

    };

}


#endif //BITOCEN_CRYPTOCONTEXT_H

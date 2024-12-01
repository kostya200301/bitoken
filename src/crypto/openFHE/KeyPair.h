//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_KEYPAIR_H
#define BITOCEN_KEYPAIR_H

#include <string>
#include "openfhe.h"
#include "crypto/IKeyPair.h"


namespace crypto {

    class KeyPair : public IKeyPair {
    public:

        KeyPair(const lbcrypto::KeyPair<lbcrypto::DCRTPoly>& key_pair);

        ~KeyPair() override;

        const IPublicKeyPtr get_pk() const override;

        const ISecretKeyPtr get_sk() const override;

    private:
        lbcrypto::KeyPair<lbcrypto::DCRTPoly> key_pair_;
    };

}



#endif //BITOCEN_KEYPAIR_H

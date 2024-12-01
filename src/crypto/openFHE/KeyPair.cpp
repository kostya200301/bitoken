//
// Created by Константин Беляков on 30.11.2024.
//

#include "KeyPair.h"
#include "PublicKey.h"
#include "SecretKey.h"
#include <memory>

namespace crypto {

    KeyPair::KeyPair(const lbcrypto::KeyPair<lbcrypto::DCRTPoly>& key_pair) : key_pair_(key_pair) {}

    KeyPair::~KeyPair() = default;

    const IPublicKeyPtr KeyPair::get_pk() const {

        IPublicKeyPtr pk = std::make_shared<PublicKey>(key_pair_.publicKey);

        return pk;
    }

    const ISecretKeyPtr KeyPair::get_sk() const {

        ISecretKeyPtr sk = std::make_shared<SecretKey>(key_pair_.secretKey);

        return sk;
    }


}
//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_CRYPTOCONTEXT_H
#define BITOCEN_CRYPTOCONTEXT_H

#include "crypto/ICryptoContext.h"
#include "crypto/IPlainText.h"
#include "crypto/ICiphertext.h"
#include "crypto/IPublicKey.h"
#include "crypto/IRecryptKey.h"
#include "PublicKey.h"
#include "openfhe.h"
#include <cereal/archives/portable_binary.hpp>


namespace crypto {

    class CryptoContext : public ICryptoContext {
    public:
        CryptoContext();

        IKeyPairPtr generate_key_pair() override;

        IPlainTextPtr create_plain_text(const std::vector<int64_t>& data) override;

        ICiphertextPtr encrypt(const IPublicKeyPtr& pk, const IPlainTextPtr& pt) override;

        IPlainTextPtr decrypt(const ISecretKeyPtr& sk, const ICiphertextPtr& cipher_text) override;

        IRecryptKeyPtr generate_recrypt_key(const ISecretKeyPtr& sk, const IPublicKeyPtr& pk) override;

        ICiphertextPtr reencrypt(const ICiphertextPtr& cipher_text, const IRecryptKeyPtr& rekey) override;


    private:
        lbcrypto::CryptoContext<lbcrypto::DCRTPoly> cc;
    };

}


#endif //BITOCEN_CRYPTOCONTEXT_H

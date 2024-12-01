//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_ICRYPTOCONTEXT_H
#define BITOCEN_ICRYPTOCONTEXT_H

#include <memory>
#include "IKeyPair.h"
#include "IPlainText.h"
#include "ICiphertext.h"
#include "IPublicKey.h"
#include "IRecryptKey.h"

namespace crypto {

    class ICryptoContext;
    using ICryptoContextPtr = std::shared_ptr<ICryptoContext>;

    class ICryptoContext {
    public:
        virtual IKeyPairPtr generate_key_pair() = 0;

        virtual IPlainTextPtr create_plain_text(const std::vector<int64_t>& data) = 0;

        virtual ICiphertextPtr encrypt(const IPublicKeyPtr& pk, const IPlainTextPtr& pt) = 0;

        virtual IPlainTextPtr decrypt(const ISecretKeyPtr& sk, const ICiphertextPtr& cipher_text) = 0;

        virtual IRecryptKeyPtr generate_recrypt_key(const ISecretKeyPtr& sk, const IPublicKeyPtr& pk) = 0;

        virtual ICiphertextPtr reencrypt(const ICiphertextPtr& cipher_text, const IRecryptKeyPtr& rekey) = 0;
    };

}


#endif //BITOCEN_ICRYPTOCONTEXT_H

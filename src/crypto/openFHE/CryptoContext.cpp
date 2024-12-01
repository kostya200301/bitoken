//
// Created by Константин Беляков on 29.11.2024.
//

#include "CryptoContext.h"
#include <spdlog/spdlog.h>
#include "KeyPair.h"
#include "PlainText.h"
#include "SecretKey.h"
#include "RecryptKey.h"
#include "Ciphertext.h"

size_t RING_DIM = 2048;
size_t plaintextModulus = 65536;

namespace crypto {
    CryptoContext::CryptoContext() {
        lbcrypto::CCParams<lbcrypto::CryptoContextBGVRNS> parameters;

        parameters.SetPREMode(lbcrypto::INDCPA);
        parameters.SetKeySwitchTechnique(lbcrypto::HYBRID);
        parameters.SetRingDim(RING_DIM);
        parameters.SetPlaintextModulus(plaintextModulus);

        parameters.SetSecurityLevel(lbcrypto::SecurityLevel::HEStd_NotSet);

        cc = GenCryptoContext(parameters);

        cc->Enable(lbcrypto::PKE);
        cc->Enable(lbcrypto::KEYSWITCH);
        cc->Enable(lbcrypto::LEVELEDSHE);
        cc->Enable(lbcrypto::PRE);
    }

    IKeyPairPtr CryptoContext::generate_key_pair() {
        spdlog::trace("[crypto] CryptoContext: start generate key pair");
        lbcrypto::KeyPair<lbcrypto::DCRTPoly> keyPair;

        keyPair = cc->KeyGen();

        if (!keyPair.good()) {
            spdlog::error("Key generation failed!");
            return nullptr;
        }

        return std::make_shared<KeyPair>(keyPair);
    }

    IPlainTextPtr CryptoContext::create_plain_text(const std::vector<int64_t>& data) {
        spdlog::trace("[crypto] CryptoContext create PlainText by vecInt64");

        std::vector<int64_t> vecData;
        vecData.reserve(data.size());

        for (long long i : data)
            vecData.push_back(i);

        auto pt = cc->MakeCoefPackedPlaintext(vecData);

        return std::make_shared<PlainText>(pt);
    }

    ICiphertextPtr CryptoContext::encrypt(const IPublicKeyPtr & pk, const IPlainTextPtr& pt) {
        spdlog::trace("[crypto] CryptoContext: start encrypt");

        PublicKeyPtr pub_key = std::dynamic_pointer_cast<PublicKey>(pk);
        PlainTextPtr plain_text = std::dynamic_pointer_cast<PlainText>(pt);

        if (pub_key && plain_text) {
            return std::make_shared<Ciphertext>(cc->Encrypt(pub_key->data_, plain_text->pt_));
        } else {
            spdlog::error("[crypto] CryptoContext: Error transform IPublicKeyPtr to FHE PublicKeyPtr or IPlainTextPtr to FHE PlainTextPtr");
            return nullptr;
        }
    }

    IPlainTextPtr CryptoContext::decrypt(const ISecretKeyPtr & sk, const ICiphertextPtr& cipher_text) {
        spdlog::trace("[crypto] CryptoContext: start decrypt");
        SecretKeyPtr sec_key = std::dynamic_pointer_cast<SecretKey>(sk);
        CiphertextPtr cip_txt = std::dynamic_pointer_cast<Ciphertext>(cipher_text);


        if (sec_key && cip_txt) {
            std::shared_ptr<lbcrypto::PlaintextImpl> ptDec1;
            cc->Decrypt(sec_key->data_, cip_txt->data_, &ptDec1);
            return std::make_shared<PlainText>(ptDec1);
        } else {
            spdlog::error("[crypto] CryptoContext: Error transform ISecretKeyPtr to FHE SecretKeyPtr or ICiphertextPtr to FHE CiphertextPtr");
            return nullptr;
        }

    }

    IRecryptKeyPtr CryptoContext::generate_recrypt_key(const ISecretKeyPtr& sk, const IPublicKeyPtr& pk) {
        spdlog::trace("[crypto] CryptoContext: start generate recrypt key");
        SecretKeyPtr sec_key = std::dynamic_pointer_cast<SecretKey>(sk);
        PublicKeyPtr pub_key = std::dynamic_pointer_cast<PublicKey>(pk);


        if (sec_key && pub_key) {
            auto key = cc->ReKeyGen(sec_key->data_, pub_key->data_);
            return std::make_shared<RecryptKey>(key);
        } else {
            spdlog::error("[crypto] CryptoContext: Error transform ISecretKeyPtr to FHE SecretKeyPtr or IPublicKeyPtr to FHE PublicKeyPtr");
            return nullptr;
        }

    }

    ICiphertextPtr CryptoContext::reencrypt(const ICiphertextPtr& cipher_text, const IRecryptKeyPtr& rekey) {
        spdlog::trace("[crypto] CryptoContext: start reencrypt");
        CiphertextPtr cip_txt = std::dynamic_pointer_cast<Ciphertext>(cipher_text);
        RecryptKeyPtr re_key = std::dynamic_pointer_cast<RecryptKey>(rekey);


        if (cip_txt && re_key) {
            auto ct = cc->ReEncrypt(cip_txt->data_, re_key->key_);
            return std::make_shared<Ciphertext>(ct);
        } else {
            spdlog::error("[crypto] CryptoContext: Error transform ICiphertextPtr to FHE CiphertextPtr or IRecryptKeyPtr to FHE RecryptKeyPtr");
            return nullptr;
        }
    }


}
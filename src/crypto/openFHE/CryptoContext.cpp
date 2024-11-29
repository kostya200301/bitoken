//
// Created by Константин Беляков on 29.11.2024.
//

#include "CryptoContext.h"

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

    KeyPairPtr CryptoContext::GenerateFHEKeyPair() {
        return nullptr;
    }
}
//
// Created by Константин Беляков on 30.11.2024.
//

#include "SecretKey.h"

namespace crypto {

    SecretKey::SecretKey(lbcrypto::PrivateKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data) : data_(data) {}

    SecretKey::~SecretKey() = default;

    [[nodiscard]] const std::string SecretKey::get_string() const {

        std::ostringstream os;
        {
            cereal::PortableBinaryOutputArchive archive(os);
            std::uint32_t version = 1; // tmp
            data_->save(archive, version);
        }

        std::string sk_sting = os.str();

        return sk_sting;
    }

}
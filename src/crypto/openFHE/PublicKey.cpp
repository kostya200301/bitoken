//
// Created by Константин Беляков on 30.11.2024.
//

#include "PublicKey.h"

namespace crypto {

    PublicKey::PublicKey(lbcrypto::PublicKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data) : data_(data) {}

    PublicKey::~PublicKey() = default;

    [[nodiscard]] const std::string PublicKey::get_string() const {

        std::ostringstream ps;
        {
            cereal::PortableBinaryOutputArchive archive(ps);
            std::uint32_t version = 1; // tmp
            data_->save(archive, version);
        }

        std::string pk_sting = ps.str();

        return pk_sting;
    }

}
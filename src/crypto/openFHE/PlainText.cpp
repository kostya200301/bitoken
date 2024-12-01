//
// Created by Константин Беляков on 30.11.2024.
//

#include "PlainText.h"

namespace crypto {

    PlainText::PlainText(std::shared_ptr<lbcrypto::PlaintextImpl> const& pt) : pt_(pt) {}

    PlainText::~PlainText() = default;

    const std::vector<int64_t> PlainText::get_int64_vec() const {
        return pt_->GetCoefPackedValue();
    }

}
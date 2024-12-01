//
// Created by Константин Беляков on 30.11.2024.
//

#include "RecryptKey.h"

namespace crypto {

    RecryptKey::RecryptKey(lbcrypto::EvalKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> key) : key_(key) {}

    RecryptKey::~RecryptKey() = default;
}

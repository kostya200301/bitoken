//
// Created by Константин Беляков on 30.11.2024.
//

#include "Ciphertext.h"

namespace crypto {

    Ciphertext::Ciphertext(lbcrypto::Ciphertext<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> data) : data_(data) {}

    Ciphertext::~Ciphertext() = default;



}

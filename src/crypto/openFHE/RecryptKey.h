//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_RECRYPTKEY_H
#define BITOCEN_RECRYPTKEY_H

#include "openfhe.h"
#include "crypto/IRecryptKey.h"


namespace crypto {

    class RecryptKey;
    using RecryptKeyPtr = std::shared_ptr<RecryptKey>;

    class RecryptKey : public IRecryptKey {
    public:

        RecryptKey(lbcrypto::EvalKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> key);

        ~RecryptKey() override;

    public:
        lbcrypto::EvalKey<lbcrypto::DCRTPolyImpl<bigintdyn::mubintvec<bigintdyn::ubint<unsigned long long>>>> key_;
    };

}

#endif //BITOCEN_RECRYPTKEY_H

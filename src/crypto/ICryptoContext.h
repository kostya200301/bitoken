//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_ICRYPTOCONTEXT_H
#define BITOCEN_ICRYPTOCONTEXT_H

#include <memory>
#include "KeyPair.h"

namespace crypto {

    class ICryptoContext;
    using ICryptoContextPtr = std::shared_ptr<ICryptoContext>;

    class ICryptoContext {
        virtual KeyPairPtr GenerateFHEKeyPair() = 0;
    };

}


#endif //BITOCEN_ICRYPTOCONTEXT_H

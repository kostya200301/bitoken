//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_IKEYGENERATOR_H
#define BITOCEN_IKEYGENERATOR_H

#include <memory>
#include "IKeyPair.h"

namespace crypto {

    class IKeysGenerator;
    using IKeysGeneratorPtr = std::shared_ptr<IKeysGenerator>;

    class IKeysGenerator {
        virtual IKeyPairPtr GenerateFHEKeyPair() = 0;
    };

}

#endif //BITOCEN_IKEYGENERATOR_H

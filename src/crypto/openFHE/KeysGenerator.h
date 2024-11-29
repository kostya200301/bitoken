//
// Created by Константин Беляков on 29.11.2024.
//

#ifndef BITOCEN_KEYSGENERATOR_H
#define BITOCEN_KEYSGENERATOR_H

#include "crypto/KeyPair.h"
#include "crypto/IKeysGenerator.h"

namespace crypto{

    class KeysGenerator : IKeysGenerator {

        KeyPairPtr GenerateFHEKeyPair() override;
    };

}


#endif //BITOCEN_KEYSGENERATOR_H

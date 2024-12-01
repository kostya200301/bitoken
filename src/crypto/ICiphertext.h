//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_ICIPHERTEXT_H
#define BITOCEN_ICIPHERTEXT_H

#include <memory>

namespace crypto {

    class ICiphertext;
    using ICiphertextPtr = std::shared_ptr<ICiphertext>;

    class ICiphertext {
    public:
        virtual ~ICiphertext() = default;

    };

}

#endif //BITOCEN_ICIPHERTEXT_H

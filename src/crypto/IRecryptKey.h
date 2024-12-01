//
// Created by Константин Беляков on 30.11.2024.
//

#ifndef BITOCEN_IRECRYPTKEY_H
#define BITOCEN_IRECRYPTKEY_H

#include <memory>

namespace crypto {

    class IRecryptKey;
    using IRecryptKeyPtr = std::shared_ptr<IRecryptKey>;

    class IRecryptKey {
    public:

        virtual ~IRecryptKey() = default;
    };

}


#endif //BITOCEN_IRECRYPTKEY_H

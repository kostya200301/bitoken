//
// Created by Константин Беляков on 15.12.2024.
//

#ifndef BITOCEN_IDBINITIALIZER_H
#define BITOCEN_IDBINITIALIZER_H

#include "db/IDBConnection.h"
#include <memory>

namespace db {

    class IDBInitializer;
    using IDBInitializerPtr = std::shared_ptr<IDBInitializer>;

    class IDBInitializer {
    public:

        virtual ~IDBInitializer() = default;

        virtual void init() = 0;

    };

}


#endif //BITOCEN_IDBINITIALIZER_H

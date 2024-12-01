//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBQUERYITERATOR_H
#define BITOCEN_IDBQUERYITERATOR_H

#include <memory>
#include "IDBRow.h"

namespace db {

    class IDBQueryIterator;
    using IDBQueryIteratorPtr = std::shared_ptr<IDBQueryIterator>;

    class IDBQueryIterator {
    public:

        virtual ~IDBQueryIterator() = default;

        virtual IDBRowPtr get_row() = 0;

        virtual bool next() = 0;
    };

}


#endif //BITOCEN_IDBQUERYITERATOR_H

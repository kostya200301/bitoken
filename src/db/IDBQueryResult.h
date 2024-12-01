//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBQUERYRESULT_H
#define BITOCEN_IDBQUERYRESULT_H

#include <memory>
#include "IDBQueryIterator.h"

namespace db {

    class IDBQueryResult;
    using IDBQueryResultPtr = std::shared_ptr<IDBQueryResult>;

    class IDBQueryResult {
    public:
        virtual ~IDBQueryResult() = default;

        virtual IDBQueryIteratorPtr get_iterator() = 0;

    };

}



#endif //BITOCEN_IDBQUERYRESULT_H

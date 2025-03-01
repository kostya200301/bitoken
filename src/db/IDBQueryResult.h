//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBQUERYRESULT_H
#define BITOCEN_IDBQUERYRESULT_H

#include <memory>
#include "IDBQueryIterator.h"
#include "IDBQuery.h"

namespace db {

    class IDBQueryResult;
    using IDBQueryResultPtr = std::shared_ptr<IDBQueryResult>;

    class IDBQueryResult {
    public:
        virtual ~IDBQueryResult() = default;

        virtual IDBQueryIteratorPtr get_iterator() = 0;

        virtual IDBQueryPtr get_query() = 0;

        virtual void set_query(const IDBQueryPtr& query) = 0;
    };

}



#endif //BITOCEN_IDBQUERYRESULT_H

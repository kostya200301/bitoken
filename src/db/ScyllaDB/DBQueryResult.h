//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBQUERYRESULT_H
#define BITOCEN_DBQUERYRESULT_H

#include "db/IDBQueryResult.h"
#include "cassandra.h"

namespace db {

    class DBQueryResult;
    using DBQueryResultPtr = std::shared_ptr<DBQueryResult>;

    class DBQueryResult : public IDBQueryResult {
    public:
        DBQueryResult(const CassResult* result);

        ~DBQueryResult() override;

        IDBQueryIteratorPtr get_iterator() override;

    private:
        const CassResult* result_;
    };

}


#endif //BITOCEN_DBQUERYRESULT_H

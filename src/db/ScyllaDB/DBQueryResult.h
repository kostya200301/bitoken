//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBQUERYRESULT_H
#define BITOCEN_DBQUERYRESULT_H

#include "db/IDBQueryResult.h"
#include "db/IDBQuery.h"
#include "cassandra.h"

namespace db {

    class DBQueryResult;
    using DBQueryResultPtr = std::shared_ptr<DBQueryResult>;

    class DBQueryResult : public IDBQueryResult {
    public:
        DBQueryResult(const CassResult* result);

        ~DBQueryResult() override;

        IDBQueryIteratorPtr get_iterator() override;

        IDBQueryPtr get_query() override {
            return query_;
        }

        void set_query(const IDBQueryPtr& query) override {
            query_ = query;
        }

    private:
        const CassResult* result_;
        IDBQueryPtr query_ = nullptr;
    };

}


#endif //BITOCEN_DBQUERYRESULT_H

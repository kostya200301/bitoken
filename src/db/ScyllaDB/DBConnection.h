//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBCONNECTION_H
#define BITOCEN_DBCONNECTION_H

#include <memory>
#include "db/IDBConnection.h"

namespace db {

    class DBConnection;
    using DBConnectionPtr = std::shared_ptr<DBConnection>;

    class DBConnection : public IDBConnection {
    public:

        DBConnection();

        ~DBConnection() override;

//        virtual IFeature<IDBQueryResultPtr> execute_query_async(
//                const IDBQueryPtr& query,
//                std::function<void(const IDBQueryResultPtr&)> callback) = 0;
//
        bool connect(const DBConnectionParamsPtr& params) override;
    };

}

#endif //BITOCEN_DBCONNECTION_H

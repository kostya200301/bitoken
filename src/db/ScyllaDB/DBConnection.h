//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBCONNECTION_H
#define BITOCEN_DBCONNECTION_H

#include <memory>
#include <cassandra.h>
#include "db/IDBConnection.h"

namespace db {

    class DBConnection;
    using DBConnectionPtr = std::shared_ptr<DBConnection>;

    class DBConnection : public IDBConnection {
    public:

        DBConnection();

        ~DBConnection() override;

        IFeaturePtr<IDBQueryResultPtr> execute_query_async(
                const IDBQueryPtr& query,
                std::function<void(const IDBQueryResultPtr&)> callback) override;

        bool connect(const DBConnectionParamsPtr& params) override;

        IDBQueryResultPtr execute_query(const IDBQueryPtr& query) override;

    private:
        CassCluster *cluster_;
        CassSession *session_;
    };

}

#endif //BITOCEN_DBCONNECTION_H

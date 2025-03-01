//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBCONNECTION_H
#define BITOCEN_DBCONNECTION_H

#include <memory>
#include <cassandra.h>
#include <boost/asio.hpp>
#include "db/IDBConnection.h"
#include "tools/IoContextManager.h"

namespace db {

    class DBConnection;
    using DBConnectionPtr = std::shared_ptr<DBConnection>;

    class DBConnection : public IDBConnection {
    public:

        DBConnection(const IoContextManagerPtr& io_context_manager);

        ~DBConnection() override;

        IFeaturePtr<IDBQueryResultPtr> execute_query_async(
                const IDBQueryPtr& query,
                void(*callback)(const IFeaturePtr<IDBQueryResultPtr>&, void*)) override;

        bool connect(const DBConnectionParamsPtr& params) override;

        IDBQueryResultPtr execute_query(const IDBQueryPtr& query) override;

    private:
        IoContextManagerPtr io_context_manager_;
        CassCluster *cluster_;
        CassSession *session_;
    };

}

#endif //BITOCEN_DBCONNECTION_H

//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBCONNECTION_H
#define BITOCEN_IDBCONNECTION_H

#include "tools/IFuture.h"
#include "IDBQueryResult.h"
#include "DBConnectionParams.h"
#include "IDBQuery.h"

namespace db {

    class IDBConnection;
    using IDBConnectionPtr = std::shared_ptr<IDBConnection>;

    class IDBConnection {
    public:
        virtual ~IDBConnection() = default;

        virtual IFeature<IDBQueryResultPtr> execute_query_async(
                const IDBQueryPtr& query,
                std::function<void(const IDBQueryResultPtr&)> callback) = 0;

        virtual bool connect(const DBConnectionParamsPtr& params) = 0;

    };

}

#endif //BITOCEN_IDBCONNECTION_H

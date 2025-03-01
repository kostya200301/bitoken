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

        virtual IFeaturePtr<IDBQueryResultPtr> execute_query_async(
                const IDBQueryPtr& query,
                void(*callback)(const IFeaturePtr<IDBQueryResultPtr>&, void*)) = 0;

        virtual bool connect(const DBConnectionParamsPtr& params) = 0;

        virtual IDBQueryResultPtr execute_query(const IDBQueryPtr& query) = 0;

    };

}

#endif //BITOCEN_IDBCONNECTION_H

//
// Created by Константин Беляков on 30.12.2024.
//

#ifndef BITOCEN_REKEYSMANAGERREPO_H
#define BITOCEN_REKEYSMANAGERREPO_H

#include <memory>
#include "IDBConnection.h"
#include "tools/IFuture.h"

namespace db {

    class ReKeysManagerRepo;
    using ReKeysManagerRepPtr = std::shared_ptr<ReKeysManagerRepo>;

    class ReKeysManagerRepo {
    public:
        ReKeysManagerRepo(const IDBConnectionPtr& connection);

        IFeaturePtr<db::IDBQueryResultPtr> create_rekey();

    private:
        IDBConnectionPtr connection_;
    };


}

#endif //BITOCEN_REKEYSMANAGERREPO_H

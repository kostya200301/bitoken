//
// Created by Константин Беляков on 30.12.2024.
//

#ifndef BITOCEN_MESSAGESMANAGERREPO_H
#define BITOCEN_MESSAGESMANAGERREPO_H

#include <memory>
#include "IDBConnection.h"
#include "tools/IFuture.h"

namespace db {

    class MessagesManagerRepo;
    using MessagesManagerRepoPtr = std::shared_ptr<MessagesManagerRepo>;

    class MessagesManagerRepo {
    public:
        MessagesManagerRepo(const IDBConnectionPtr& connection);

        IFeaturePtr<db::IDBQueryResultPtr> create_message();

    private:
        IDBConnectionPtr connection_;
    };

}

#endif //BITOCEN_MESSAGESMANAGERREPO_H

//
// Created by Константин Беляков on 17.12.2024.
//

#ifndef BITOCEN_USERSMANAGERREPO_H
#define BITOCEN_USERSMANAGERREPO_H

#include <memory>

#include "model/User.h"
#include "IDBConnection.h"
#include "tools/IFuture.h"

namespace db {

    class UsersManagerRepo;
    using UsersManagerRepoPtr = std::shared_ptr<UsersManagerRepo>;

    class UsersManagerRepo {
    public:
        UsersManagerRepo(const IDBConnectionPtr& connection);

        IFeaturePtr<db::IDBQueryResultPtr> create_user();

        IFeaturePtr<db::IDBQueryResultPtr> create_user(const std::string& username, const std::string& first_name, const std::string& last_name);

        IFeaturePtr<db::IDBQueryResultPtr> create_user(const UINT8VECPtr& uuid, const std::string& username, const std::string& first_name, const std::string& last_name);

    private:
        IDBConnectionPtr connection_;
    };

}


#endif //BITOCEN_USERSMANAGERREPO_H

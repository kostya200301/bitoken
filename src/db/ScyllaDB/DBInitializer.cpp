//
// Created by Константин Беляков on 15.12.2024.
//

#include "DBInitializer.h"
#include "db/DBQuery.h"
#include "misc/FileUtils.h"
#include <spdlog/spdlog.h>

namespace db {

    DBInitializer::~DBInitializer() = default;

    void DBInitializer::init() {
        // create users table
        auto str_q_create_users_table = FileUtils::readCqlFile("/Users/konstantinbelakov/CLionProjects/bitoken/src/db/ScyllaDB/SQLScripts/CreateUsers.cql");
        spdlog::trace("[DB] DBInitializer: Query [{}]", str_q_create_users_table);
        IDBQueryPtr q_create_users_table = std::make_shared<DBQuery>();
        q_create_users_table->from_string(str_q_create_users_table);
        connection_->execute_query(q_create_users_table);

        // create messages table
        auto str_q_create_messages_table = FileUtils::readCqlFile("/Users/konstantinbelakov/CLionProjects/bitoken/src/db/ScyllaDB/SQLScripts/CreateMessages.cql");
        spdlog::trace("[DB] DBInitializer: Query [{}]", str_q_create_messages_table);
        IDBQueryPtr q_create_messages_table = std::make_shared<DBQuery>();
        q_create_messages_table->from_string(str_q_create_messages_table);
        connection_->execute_query(q_create_messages_table);

        // create reKeys table
        auto str_q_create_rekeys_table = FileUtils::readCqlFile("/Users/konstantinbelakov/CLionProjects/bitoken/src/db/ScyllaDB/SQLScripts/CreateReKeys.cql");
        spdlog::trace("[DB] DBInitializer: Query [{}]", str_q_create_rekeys_table);
        IDBQueryPtr q_create_rekeys_table = std::make_shared<DBQuery>();
        q_create_rekeys_table->from_string(str_q_create_rekeys_table);
        connection_->execute_query(q_create_rekeys_table);
    }

    DBInitializer::DBInitializer(const IDBConnectionPtr& connection) : connection_(connection) {}

}
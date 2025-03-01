//
// Created by Константин Беляков on 17.12.2024.
//

#include "UsersManagerRepo.h"
#include "DBQuery.h"
#include "crypto/CryptoHelper.h"

namespace db {

    UsersManagerRepo::UsersManagerRepo(const IDBConnectionPtr& connection) : connection_(connection) {}

    IFeaturePtr<db::IDBQueryResultPtr> UsersManagerRepo::create_user() {
        IDBQueryPtr q = std::make_shared<DBQuery>();
        std::string q_str = "INSERT INTO users (id, username, first_name, last_name, profile_photo_url, key_version, created_at) VALUES (?, ?, ?, ?, ?, 0, toTimestamp(now()))";
        q->from_string(q_str);
        std::string default_str = "default";
        std::string user_name = crypto::CryptoHelper::generate_random_string(15);
        UINT8VECPtr data_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        q->set_param(0, db::DBQueryParam(data_id));
        q->set_param(1, db::DBQueryParam(user_name));
        q->set_param(2, db::DBQueryParam(default_str));
        q->set_param(3, db::DBQueryParam(default_str));
        q->set_param(4, db::DBQueryParam(default_str));
        return connection_->execute_query_async(q, nullptr);
    }

    IFeaturePtr<db::IDBQueryResultPtr> UsersManagerRepo::create_user(const std::string& username, const std::string& first_name, const std::string& last_name) {
        IDBQueryPtr q = std::make_shared<DBQuery>();
        std::string q_str = "INSERT INTO users (id, username, first_name, last_name, profile_photo_url, key_version, created_at) VALUES (?, ?, ?, ?, ?, 0, toTimestamp(now()))";
        q->from_string(q_str);
        std::string profile_photo_url = "/user/lala.png";
        UINT8VECPtr data_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        q->set_param(0, db::DBQueryParam(data_id));
        q->set_param(1, db::DBQueryParam(username));
        q->set_param(2, db::DBQueryParam(first_name));
        q->set_param(3, db::DBQueryParam(last_name));
        q->set_param(4, db::DBQueryParam(profile_photo_url));
        return connection_->execute_query_async(q, nullptr);
    }

    IFeaturePtr<db::IDBQueryResultPtr> UsersManagerRepo::create_user(const UINT8VECPtr& uuid, const std::string& username, const std::string& first_name, const std::string& last_name) {
        IDBQueryPtr q = std::make_shared<DBQuery>();
        std::string q_str = "INSERT INTO users (id, username, first_name, last_name, profile_photo_url, key_version, created_at) VALUES (?, ?, ?, ?, ?, 0, toTimestamp(now()))";
        q->from_string(q_str);
        std::string profile_photo_url = "/user/lala.png";
        q->set_param(0, db::DBQueryParam(uuid));
        q->set_param(1, db::DBQueryParam(username));
        q->set_param(2, db::DBQueryParam(first_name));
        q->set_param(3, db::DBQueryParam(last_name));
        q->set_param(4, db::DBQueryParam(profile_photo_url));
        return connection_->execute_query_async(q, nullptr);
    }

}
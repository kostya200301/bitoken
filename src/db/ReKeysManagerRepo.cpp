//
// Created by Константин Беляков on 30.12.2024.
//

#include "ReKeysManagerRepo.h"
#include "DBQuery.h"
#include "crypto/CryptoHelper.h"

namespace db {

    ReKeysManagerRepo::ReKeysManagerRepo(const IDBConnectionPtr& connection) : connection_(connection) {}

    IFeaturePtr<db::IDBQueryResultPtr> ReKeysManagerRepo::create_rekey() {
        IDBQueryPtr q = std::make_shared<DBQuery>();
        std::string q_str = "INSERT INTO reKeys (id, sender_id, receiver_id, sender_key_version, receiver_key_version, created_at) VALUES (?, ?, ?, ?, ?, toTimestamp(now()))";
        q->from_string(q_str);
        std::string default_str = "default";
        std::string user_name = crypto::CryptoHelper::generate_random_string(15);
        UINT8VECPtr id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        UINT8VECPtr sender_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        UINT8VECPtr receiver_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        q->set_param(0, db::DBQueryParam(id));
        q->set_param(1, db::DBQueryParam(sender_id));
        q->set_param(2, db::DBQueryParam(receiver_id));
        q->set_param(3, db::DBQueryParam(0));
        q->set_param(4, db::DBQueryParam(0));
        return connection_->execute_query_async(q, nullptr);
    }
}
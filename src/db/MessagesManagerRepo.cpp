//
// Created by Константин Беляков on 30.12.2024.
//

#include "MessagesManagerRepo.h"
#include "DBQuery.h"
#include "crypto/CryptoHelper.h"

namespace db {

    MessagesManagerRepo::MessagesManagerRepo(const IDBConnectionPtr& connection) : connection_(connection) {}

    IFeaturePtr<db::IDBQueryResultPtr> MessagesManagerRepo::create_message() {
        IDBQueryPtr q = std::make_shared<DBQuery>();
        std::string q_str = "INSERT INTO messages (id, chat_id, sender_id, data, sender_key_version, date_time) VALUES (?, ?, ?, ?, ?, ?)";
        q->from_string(q_str);
        std::string default_str = "default";
        UINT8VECPtr message_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        UINT8VECPtr chat_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        UINT8VECPtr sender_id = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
        q->set_param(0, db::DBQueryParam(message_id));
        q->set_param(1, db::DBQueryParam(chat_id));
        q->set_param(2, db::DBQueryParam(sender_id));
        q->set_param(3, db::DBQueryParam(default_str));
        q->set_param(4, db::DBQueryParam(0));

        q->set_param(5, db::DBQueryParam(std::chrono::duration_cast< std::chrono::milliseconds >(
                std::chrono::system_clock::now().time_since_epoch()
        ).count()));
        return connection_->execute_query_async(q, nullptr);
    }

}
//
// Created by Константин Беляков on 01.12.2024.
//

#include <iostream>
#include <spdlog/spdlog.h>
#include "DBConnection.h"
#include "DBQueryResult.h"

namespace db {

    DBConnection::DBConnection() {}

    DBConnection::~DBConnection() {
        spdlog::info("[db] DBConnection: Destroy Scylla DBConnection");
        cass_cluster_free(cluster_);
        cass_session_free(session_);
    }

    bool DBConnection::connect(const DBConnectionParamsPtr& params) {
        cluster_ = cass_cluster_new();
        session_ = cass_session_new();
        const char *hosts = "127.0.0.1";

        // Настройка контактных точек
        cass_cluster_set_contact_points(cluster_, hosts);

        // Подключаемся к кластеру
        CassFuture *connect_future = cass_session_connect(session_, cluster_);
        if (cass_future_error_code(connect_future) == CASS_OK) {
            spdlog::info("[db] DBConnection: Connected to ScyllaDB cluster");

            // Используем ключевое пространство
            std::string keyspace = "test_keyspace";
            const char *use_keyspace_query = "USE test_keyspace;";
            CassStatement *use_keyspace_statement = cass_statement_new(use_keyspace_query, 0);
            CassFuture *use_keyspace_future = cass_session_execute(session_, use_keyspace_statement);

            if (cass_future_error_code(use_keyspace_future) == CASS_OK) {
                spdlog::info("[db] DBConnection: Using keyspace {}", keyspace);
            } else {
                const char *message;
                size_t message_length;
                cass_future_error_message(use_keyspace_future, &message, &message_length);
                spdlog::error("[db] DBConnection: Unable to use keyspace: {}, err: {}", keyspace, std::string(message, message_length));
                cass_future_free(use_keyspace_future);
                return false;
            }

            cass_future_free(use_keyspace_future);
            cass_statement_free(use_keyspace_statement);
        }

        return true;
    }

    IFeaturePtr<IDBQueryResultPtr> DBConnection::execute_query_async (
            const IDBQueryPtr& query,
            std::function<void(const IDBQueryResultPtr&)> callback) {

        return nullptr;
    }

    IDBQueryResultPtr DBConnection::execute_query(const IDBQueryPtr& query) {

        CassStatement* statement = cass_statement_new(query->get_string_query().c_str(), query->get_num_parameters());

        for (size_t i = 0; i < query->get_num_parameters(); ++i) {
            const auto& param = query->get_param(i);
            switch (param.get_type()) {
                case DBQueryParam::ParameterType::STRING:
                        cass_statement_bind_string(statement, i, param.get_value<std::string>().c_str());
                    break;
                case DBQueryParam::ParameterType::INT:
                        cass_statement_bind_int32(statement, i, param.get_value<int>());
                    break;
                case DBQueryParam::ParameterType::FLOAT:
                    cass_statement_bind_float(statement, i, param.get_value<float>());
                    break;
                case DBQueryParam::ParameterType::BOOL:
                    cass_statement_bind_bool(statement, i, param.get_value<bool>() ? cass_true : cass_false);
                    break;
                default:
                    spdlog::warn("[db] DBConnection::execute_query Unknown param type");
                    return nullptr;  // Или выбросить исключение
            }
        }

        CassFuture* future = cass_session_execute(session_, statement);

        cass_future_wait(future);

        CassError rc = cass_future_error_code(future);
        if (rc != CASS_OK) {
            const char* error_message;
            size_t error_message_length;
            cass_future_error_message(future, &error_message, &error_message_length);
            std::string error_msg(error_message, error_message_length);

            cass_future_free(future);
            cass_statement_free(statement);

            spdlog::error("[db] DBConnection: Insert error: {}", error_msg);
            throw std::runtime_error("Ошибка при выполнении запроса: " + error_msg);
        }

        spdlog::trace("[db] DBConnection: Insert sucsecc");


        const CassResult* result = cass_future_get_result(future);

        cass_future_free(future);
        cass_statement_free(statement);

        return std::make_shared<DBQueryResult>(result);
    }
}
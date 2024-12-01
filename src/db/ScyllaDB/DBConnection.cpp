//
// Created by Константин Беляков on 01.12.2024.
//

#include "DBConnection.h"

namespace db {

    DBConnection::DBConnection() {}

    DBConnection::~DBConnection() = default;

    bool connect(const DBConnectionParamsPtr& params) {
//        CassCluster* cluster = cass_cluster_new();
//        CassSession* session = cass_session_new();
//        const char* hosts = "127.0.0.1";
//        if (argc > 1) {
//            hosts = argv[1];
//        }
//
//        // Настройка контактных точек
//        cass_cluster_set_contact_points(cluster, hosts);
//
//        // Подключаемся к кластеру
//        CassFuture* connect_future = cass_session_connect(session, cluster);
//        if (cass_future_error_code(connect_future) == CASS_OK) {
//            std::cout << "Connected to ScyllaDB cluster." << std::endl;
//
//            // Используем ключевое пространство
//            const char* use_keyspace_query = "USE test_keyspace;";
//            CassStatement* use_keyspace_statement = cass_statement_new(use_keyspace_query, 0);
//            CassFuture* use_keyspace_future = cass_session_execute(session, use_keyspace_statement);
//
//            if (cass_future_error_code(use_keyspace_future) == CASS_OK) {
//                std::cout << "Using keyspace 'test_keyspace'." << std::endl;
//            } else {
//                const char* message;
//                size_t message_length;
//                cass_future_error_message(use_keyspace_future, &message, &message_length);
//                std::cerr << "Unable to use keyspace: '" << std::string(message, message_length) << "'" << std::endl;
//                cass_future_free(use_keyspace_future);
//                return 1;
//            }
//
//            cass_future_free(use_keyspace_future);
//            cass_statement_free(use_keyspace_statement);
    }

}
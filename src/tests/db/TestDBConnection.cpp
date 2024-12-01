#include "catch2/catch.hpp"

#include <spdlog/spdlog.h>
#include "db/ScyllaDB/DBConnection.h"
#include "db/DBQuery.h"

#include <chrono>
#include <iostream>


TEST_CASE("Test DB connection", "[db][unit][coverage]") {

    db::IDBConnectionPtr connection = std::make_shared<db::DBConnection>();
    connection->connect(nullptr);

    std::string query_str = "INSERT INTO messages (user_id, message) VALUES (uuid(), ?)";

    db::IDBQueryPtr query = std::make_shared<db::DBQuery>();
    query->from_string(query_str);
    std::string data = "sosiska";
    query->set_param(0, db::DBQueryParam(data));

    db::IDBQueryResultPtr res1 = connection->execute_query(query);


    std::string query_get_str = "SELECT * FROM messages WHERE message = ?";

    db::IDBQueryPtr query2 = std::make_shared<db::DBQuery>();
    query2->from_string(query_get_str);
    query2->set_param(0, db::DBQueryParam(data));

    db::IDBQueryResultPtr res2 = connection->execute_query(query2);


    auto iter = res2->get_iterator();

    while (iter->next()) {
        auto message = iter->get_row()->get_value(1)->get_string();
        CHECK(message == data);
    }

}
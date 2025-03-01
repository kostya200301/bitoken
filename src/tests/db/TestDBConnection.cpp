#include "catch2/catch.hpp"

#include <spdlog/spdlog.h>
#include "db/ScyllaDB/DBConnection.h"
#include "db/DBQuery.h"


#include "tools/IoContextManager.h"

void check_message_insert(const IFeaturePtr<db::IDBQueryResultPtr>& res, void* data) {
    if (res->has_error()) {
        spdlog::error("Catch {}", res->error()->get_string());
    } else {
        auto dat = res->get_result();
    }
}

std::string generateRandomString(int n) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string randomString;
    randomString.reserve(n);

    // Используем случайный генератор
    std::mt19937 generator(static_cast<unsigned long>(std::time(0))); // Инициализируем генератор случайных чисел
    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);

    // Генерируем строку
    for (int i = 0; i < n; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}

TEST_CASE("Test DB connection", "[db][unit][coverage]") {

    IoContextManagerPtr io_context_manager = std::make_shared<IoContextManager>(20);

    io_context_manager->start();

    db::IDBConnectionPtr connection = std::make_shared<db::DBConnection>(io_context_manager);
    connection->connect(nullptr);

    int N = 50000;


    std::string query_str = "INSERT INTO messages (user_id, message) VALUES (uuid(), ?)";



    spdlog::info("[test] Start insert");



    for (int i = 0; i < N; i++) {
        if (i % 10000 == 0) spdlog::info("[test] I: {}", i);

        db::IDBQueryPtr query = std::make_shared<db::DBQuery>();
        query->from_string(query_str);
        std::string data = generateRandomString(400);
        query->set_param(0, db::DBQueryParam(data));

        std::this_thread::sleep_for(std::chrono::nanoseconds(5555));
        auto res = connection->execute_query_async(query, check_message_insert);
//        res->wait();
    }

    spdlog::info("[test] End insert");




//    std::string query_str = "INSERT INTO messages (user_id, message) VALUES (uuid(), ?)";
//
//    db::IDBQueryPtr query = std::make_shared<db::DBQuery>();
//    query->from_string(query_str);
//    std::string data = "sosiska";
//    query->set_param(0, db::DBQueryParam(data));

//    for (int i = 0; i < 10000; i++)
//        db::IDBQueryResultPtr res1 = connection->execute_query(nullptr);

//    std::vector<IFeaturePtr<db::IDBQueryResultPtr>> vec;
//    for (int i = 0; i < 100; i++) {
//        spdlog::info("ADD");
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        connection->execute_query_async(query, nullptr);
//    }

//    io_context.run();


//    std::string query_get_str = "SELECT * FROM messages WHERE message = ?";
//
//    db::IDBQueryPtr query2 = std::make_shared<db::DBQuery>();
//    query2->from_string(query_get_str);
//    query2->set_param(0, db::DBQueryParam(data));
//
//    db::IDBQueryResultPtr res2 = connection->execute_query(query2);
//
//
//    auto iter = res2->get_iterator();
//
//    while (iter->next()) {
//        auto message = iter->get_row()->get_value(1)->get_string();
//        CHECK(message == data);
//    }

    std::this_thread::sleep_for(std::chrono::seconds(10));


}
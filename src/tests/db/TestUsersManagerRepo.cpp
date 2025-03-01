#include "catch2/catch.hpp"

#include <spdlog/spdlog.h>
#include "db/ScyllaDB/DBConnection.h"
#include "db/DBQuery.h"
#include "db/UsersManagerRepo.h"

#include "tools/IoContextManager.h"
#include "db/IDBInitializer.h"
#include "db/ScyllaDB/DBInitializer.h"
#include "tests/TestUtils.h"
#include "crypto/CryptoHelper.h"

//TEST_CASE("Test DB UsersManagerRepo add default users", "[db][unit][coverage]") {
//    IoContextManagerPtr io_context_manager = std::make_shared<IoContextManager>(20);
//
//    io_context_manager->start();
//
//    db::IDBConnectionPtr connection = std::make_shared<db::DBConnection>(io_context_manager);
//    connection->connect(nullptr);
//
//    db::IDBInitializerPtr initer = std::make_shared<db::DBInitializer>(connection);
//
//    initer->init();
//
//    for (int i = 0; i < 10; i++) {
//        auto repo = std::make_shared<db::UsersManagerRepo>(connection);
//        auto feature = repo->create_user();
//        SLEEP_NS(7777);
//    }
//    SLEEP_S(5);
//
//}

TEST_CASE("Test DB UsersManagerRepo create 2 users with name", "[db][unit][coverage]") {
    IoContextManagerPtr io_context_manager = std::make_shared<IoContextManager>(20);

    io_context_manager->start();

    db::IDBConnectionPtr connection = std::make_shared<db::DBConnection>(io_context_manager);
    connection->connect(nullptr);

    db::IDBInitializerPtr initer = std::make_shared<db::DBInitializer>(connection);

    initer->init();

    auto repo = std::make_shared<db::UsersManagerRepo>(connection);

    db::UINT8VECPtr data_id1 = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());
    db::UINT8VECPtr data_id2 = std::make_shared<std::vector<unsigned char>>(crypto::CryptoHelper::generate_uuid_uint8_vec());

    auto feature1 = repo->create_user(data_id1, "user1", "kostya", "belyakoff");
    auto feature2 = repo->create_user(data_id2, "user2", "Yulka", "belyakoffa");

    feature1->wait();
    feature2->wait();

    auto data1 = feature1->get_result();
    auto data2 = feature2->get_result();

    auto q1 = data1->get_query();
    auto q2 = data2->get_query();

    auto res1 = q1->get_param(0);
    auto res2 = q2->get_param(0);

    CHECK(res1.get_type() == db::DBQueryParam::ParameterType::UINT8VEC);
    CHECK(res2.get_type() == db::DBQueryParam::ParameterType::UINT8VEC);

    auto uVec8_1 = res1.get_value<db::UINT8VECPtr>();
    auto uVec8_2 = res2.get_value<db::UINT8VECPtr>();

    CHECK(uVec8_1 == data_id1);
    CHECK(uVec8_2 == data_id2);

    SLEEP_S(5);
}
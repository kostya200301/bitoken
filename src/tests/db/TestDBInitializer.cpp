#include "catch2/catch.hpp"

#include <spdlog/spdlog.h>
#include "db/ScyllaDB/DBConnection.h"
#include "db/DBQuery.h"

#include "tools/IoContextManager.h"
#include "db/IDBInitializer.h"
#include "db/ScyllaDB/DBInitializer.h"
#include "tests/TestUtils.h"

TEST_CASE("Test DB Initializer", "[db][unit][coverage]") {
    IoContextManagerPtr io_context_manager = std::make_shared<IoContextManager>(20);

    io_context_manager->start();

    db::IDBConnectionPtr connection = std::make_shared<db::DBConnection>(io_context_manager);
    connection->connect(nullptr);

    db::IDBInitializerPtr initer = std::make_shared<db::DBInitializer>(connection);

    initer->init();


    CHECK(1 == 1);

}
#include "catch2/catch.hpp"

#include <spdlog/spdlog.h>
#include "db/ScyllaDB/DBConnection.h"
#include "db/DBQuery.h"
#include "db/MessagesManagerRepo.h"

#include "tools/IoContextManager.h"
#include "db/IDBInitializer.h"
#include "db/ScyllaDB/DBInitializer.h"
#include "tests/TestUtils.h"

TEST_CASE("Test DB MessagesManagerRepo add default users", "[db][unit][coverage]") {
    IoContextManagerPtr io_context_manager = std::make_shared<IoContextManager>(20);

    io_context_manager->start();

    db::IDBConnectionPtr connection = std::make_shared<db::DBConnection>(io_context_manager);
    connection->connect(nullptr);

    db::IDBInitializerPtr initer = std::make_shared<db::DBInitializer>(connection);

    initer->init();

    for (int i = 0; i < 10; i++) {
        auto repo = std::make_shared<db::MessagesManagerRepo>(connection);
        auto feature = repo->create_message();
        SLEEP_NS(7777);
    }
    SLEEP_S(5);


}
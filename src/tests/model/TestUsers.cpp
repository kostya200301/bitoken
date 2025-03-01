#include "catch2/catch.hpp"
#include "model/User.h"
#include <memory>

using namespace std::chrono_literals;

TEST_CASE("Test Users", "[model][unit][coverage]") {
    auto user_default = std::make_shared<model::User>();

}
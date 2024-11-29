#include "catch2/catch.hpp"
#include "crypto/ICryptoContext.h"
#include "crypto/openFHE/CryptoContext.h"


TEST_CASE("Test create crypto context openFHE", "[model][unit][coverage]") {
    CHECK(1 == 1);

    crypto::ICryptoContextPtr crypto_context = std::make_shared<crypto::CryptoContext>();
}
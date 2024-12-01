#include "catch2/catch.hpp"
#include "crypto/ICryptoContext.h"
#include "crypto/openFHE/CryptoContext.h"
#include <spdlog/spdlog.h>

TEST_CASE("Test create crypto context openFHE", "[model][unit][coverage]") {

    spdlog::set_level(spdlog::level::trace);

    int N = 10000;

    std::vector<int64_t> data = {123, 123, 123, 444, 555, 666};

    auto begin = std::chrono::steady_clock::now();

    crypto::ICryptoContextPtr crypto_context = std::make_shared<crypto::CryptoContext>();

    auto keys1 = crypto_context->generate_key_pair();

    auto keys2 = crypto_context->generate_key_pair();

    auto pt = crypto_context->create_plain_text(data);

    auto enc_data = crypto_context->encrypt(keys1->get_pk(), pt);

    auto dec_data = crypto_context->decrypt(keys1->get_sk(), enc_data);

    auto rekey = crypto_context->generate_recrypt_key(keys1->get_sk(), keys2->get_pk());

    crypto::ICiphertextPtr recrypted_data = crypto_context->reencrypt(enc_data, rekey);

    auto dec_data2 = crypto_context->decrypt(keys2->get_sk(), recrypted_data);

    auto end = std::chrono::steady_clock::now();

    auto res_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    spdlog::info("Res time {} ms", res_ms.count());

    auto p1 = pt->get_int64_vec();
    auto p2 = dec_data->get_int64_vec();
    auto p3 = dec_data2->get_int64_vec();

    CHECK(std::equal(p1.begin(), p1.end(), p2.begin()));
    CHECK(std::equal(p1.begin(), p1.end(), p3.begin()));



}
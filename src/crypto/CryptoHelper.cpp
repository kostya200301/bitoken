//
// Created by Константин Беляков on 23.08.2024.
//

#include "CryptoHelper.h"
#include "spdlog/spdlog.h"
#include <random>
#include <uuid/uuid.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace crypto {

    std::string CryptoHelper::generate_random_string(size_t length) {
        const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, characters.size() - 1);

        std::string random_string;
        for (size_t i = 0; i < length; ++i) {
            random_string += characters[dis(gen)];
        }

        return random_string;
    }

    std::vector<uint8_t> CryptoHelper::generate_uuid_uint8_vec() {
        boost::uuids::random_generator generator;
        boost::uuids::uuid uuid = generator();

        std::vector<uint8_t> uuid_binary(uuid.begin(), uuid.end());
        return uuid_binary;
    }

}
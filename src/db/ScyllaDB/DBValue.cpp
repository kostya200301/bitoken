//
// Created by Константин Беляков on 01.12.2024.
//

#include "DBValue.h"

namespace db {

    DBValue::~DBValue() = default;

    DBValue::DBValue(const CassValue* value) : value_(value) {}

    std::string DBValue::get_string() {
        const char* str_value;
        size_t str_length;
        CassError error = cass_value_get_string(value_, &str_value, &str_length);
        if (error != CASS_OK) {
            throw std::runtime_error("Failed to retrieve string value from Cassandra result");
        }
        return std::string(str_value, str_length);
    }

}
//
// Created by Константин Беляков on 01.12.2024.
//

#include "DBQuery.h"

namespace db {

    DBQuery::~DBQuery() = default;

    std::string DBQuery::get_string_query() {
        return query_;
    }

    bool DBQuery::from_string(const std::string& query) {
        query_ = query;
        return true;
    }

    size_t DBQuery::get_num_parameters() {
        return num_parameters;
    }

    DBQueryParam DBQuery::get_param(size_t index) {
        return params_.at(index);
    }

    bool DBQuery::set_param(size_t index, const DBQueryParam& param) {
        params_[index] = param;
        num_parameters++;
        return true;
    }

}
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

    std::vector<size_t> DBQuery::get_params_indexes() {
        std::vector<size_t> keys;
        keys.reserve(params_.size());
        std::transform(params_.begin(), params_.end(), std::back_inserter(keys),
                       [](const std::pair<const size_t, DBQueryParam>& pair) {
                           return pair.first;
                       });
        return keys;
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
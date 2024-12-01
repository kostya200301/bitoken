//
// Created by Константин Беляков on 01.12.2024.
//

#include "DBQueryResult.h"
#include <spdlog/spdlog.h>
#include "DBQueryIterator.h"

namespace db {


    DBQueryResult::DBQueryResult(const CassResult* result) :result_(result) {}

    DBQueryResult::~DBQueryResult() {
        spdlog::info("[db] DBQueryResult: Destroy");
        cass_result_free(result_);
    }

    IDBQueryIteratorPtr DBQueryResult::get_iterator() {
        return std::make_shared<DBQueryIterator>(cass_iterator_from_result(result_));
    }

}
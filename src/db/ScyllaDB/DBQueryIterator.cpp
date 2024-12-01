//
// Created by Константин Беляков on 01.12.2024.
//

#include <spdlog/spdlog.h>
#include "DBQueryIterator.h"
#include "DBRow.h"

namespace db {

    DBQueryIterator::~DBQueryIterator() {
        spdlog::info("[db] DBQueryIterator: Destroy");
        cass_iterator_free(iterator_);
    }

    DBQueryIterator::DBQueryIterator(CassIterator* iterator) : iterator_(iterator) {}

    IDBRowPtr DBQueryIterator::get_row() {
        return std::make_shared<DBRow>(cass_iterator_get_row(iterator_));
    }

    bool DBQueryIterator::next() {
        if (cass_iterator_next(iterator_))
            return true;
        return false;
    }

}
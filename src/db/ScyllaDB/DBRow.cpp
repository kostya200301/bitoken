//
// Created by Константин Беляков on 01.12.2024.
//

#include "DBRow.h"
#include "DBValue.h"

namespace db {

    DBRow::~DBRow() = default;

    DBRow::DBRow(const CassRow* cass_row) : cass_row_(cass_row) {}

    IDBValuePtr DBRow::get_value(size_t index) {
        return std::make_shared<DBValue>(cass_row_get_column(cass_row_, index));
    }

}
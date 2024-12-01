//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBROW_H
#define BITOCEN_DBROW_H

#include "db/IDBRow.h"
#include <cassandra.h>

namespace db {

    class DBRow;
    using DBRowPtr = std::shared_ptr<DBRow>;

    class DBRow : public IDBRow {
    public:
        DBRow(const CassRow* cass_row);

        ~DBRow() override;

        IDBValuePtr get_value(size_t index) override;

    private:
        const CassRow* cass_row_;
    };

}



#endif //BITOCEN_DBROW_H

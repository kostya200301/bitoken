//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBQUERYITERATOR_H
#define BITOCEN_DBQUERYITERATOR_H

#include "db/IDBQueryIterator.h"
#include <cassandra.h>

namespace db {

    class DBQueryIterator : public IDBQueryIterator {
    public:

        DBQueryIterator(CassIterator* iterator);

        ~DBQueryIterator() override;

        IDBRowPtr get_row() override;

        bool next() override;

    private:
        CassIterator* iterator_;
    };

}

#endif //BITOCEN_DBQUERYITERATOR_H

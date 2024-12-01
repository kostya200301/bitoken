//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBVALUE_H
#define BITOCEN_DBVALUE_H

#include "db/IDBValue.h"
#include <cassandra.h>
#include <string>

namespace db {

    class DBValue;
    using DBValuePtr = std::shared_ptr<DBValue>;

    class DBValue : public IDBValue {
    public:
        DBValue(const CassValue* value);

        ~DBValue() override;

        std::string get_string() override;

    private:
        const CassValue* value_;
    };

}

#endif //BITOCEN_DBVALUE_H

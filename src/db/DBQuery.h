//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBQUERY_H
#define BITOCEN_DBQUERY_H

#include "IDBQuery.h"
#include <string>
#include <unordered_map>

namespace db {

    class DBQuery;
    using DBQueryPtr = std::shared_ptr<DBQuery>;

    class DBQuery : public IDBQuery {
    public:
        ~DBQuery() override;

        std::string get_string_query() override;

        bool from_string(const std::string& query) override;

        size_t get_num_parameters() override;

        DBQueryParam get_param(size_t index) override;

        bool set_param(size_t index, const DBQueryParam& param) override;
    private:
        std::unordered_map<size_t, DBQueryParam> params_;
        std::string query_;
        size_t num_parameters = 0;
    };

}

#endif //BITOCEN_DBQUERY_H

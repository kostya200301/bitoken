//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_DBCONNECTIONPARAMS_H
#define BITOCEN_DBCONNECTIONPARAMS_H

#include <unordered_map>
#include <string>

namespace db {

    class DBConnectionParams;
    using DBConnectionParamsPtr = std::shared_ptr<DBConnectionParams>;

    class DBConnectionParams {
    public:
        bool set_param(const std::string& param, const std::string& value);

        std::string get_param(const std::string& param) const;
    private:
        std::unordered_map<std::string, std::string> map_;

    };

}

#endif //BITOCEN_DBCONNECTIONPARAMS_H

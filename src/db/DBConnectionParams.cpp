//
// Created by Константин Беляков on 01.12.2024.
//

#include "DBConnectionParams.h"


namespace db {

    bool DBConnectionParams::set_param(const std::string& param, const std::string& value) {
        map_[param] = value;
        return true;
    }

    std::string DBConnectionParams::get_param(const std::string& param) const {
        return map_.at(param);
    }

}
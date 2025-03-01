//
// Created by Константин Беляков on 03.12.2024.
//

#include "CoreError.h"


CoreError::CoreError(const std::string& err) : error_string_(err) {}

std::string CoreError::get_string() const {
    return error_string_;
}
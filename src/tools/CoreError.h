//
// Created by Константин Беляков on 03.12.2024.
//

#ifndef BITOCEN_COREERROR_H
#define BITOCEN_COREERROR_H

#include "IError.h"

class CoreError;
using CoreErrorPtr = std::shared_ptr<CoreError>;

class CoreError : public IError {
public:
    CoreError(const std::string& err);

    std::string get_string() const override;

private:
    std::string error_string_;
};


#endif //BITOCEN_COREERROR_H

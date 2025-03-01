//
// Created by Константин Беляков on 03.12.2024.
//

#ifndef BITOCEN_IERROR_H
#define BITOCEN_IERROR_H

#include <memory>
#include <string>

class IError;
using IErrorPtr = std::shared_ptr<IError>;

class IError {
public:
    virtual std::string get_string() const = 0;
};


#endif //BITOCEN_IERROR_H

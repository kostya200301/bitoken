//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBVALUE_H
#define BITOCEN_IDBVALUE_H

#include <memory>

namespace db {

    class IDBValue;
    using IDBValuePtr = std::shared_ptr<IDBValue>;

    class IDBValue {
    public:
        virtual ~IDBValue() = default;

        virtual std::string get_string() = 0;

    };

}

#endif //BITOCEN_IDBVALUE_H

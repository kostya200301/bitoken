//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBROW_H
#define BITOCEN_IDBROW_H

#include <memory>
#include "IDBValue.h"

namespace db {

    class IDBRow;
    using IDBRowPtr = std::shared_ptr<IDBRow>;

    class IDBRow {
    public:

        virtual ~IDBRow() = default;

        virtual IDBValuePtr get_value(size_t index) = 0;

    };

}

#endif //BITOCEN_IDBROW_H

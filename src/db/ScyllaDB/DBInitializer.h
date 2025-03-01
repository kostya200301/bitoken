//
// Created by Константин Беляков on 15.12.2024.
//

#ifndef BITOCEN_DBINITIALIZER_H
#define BITOCEN_DBINITIALIZER_H

#include "db/IDBInitializer.h"

namespace db {

    class DBInitializer;
    using DBInitializerPtr = std::shared_ptr<DBInitializer>;

    class DBInitializer : public IDBInitializer {
    public:

        DBInitializer(const IDBConnectionPtr& connection);

        ~DBInitializer() override;

        void init() override;

    private:
        IDBConnectionPtr connection_;
    };

}

#endif //BITOCEN_DBINITIALIZER_H

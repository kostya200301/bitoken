//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_FEATURE_H
#define BITOCEN_FEATURE_H

#include "tools/IFuture.h"
#include "tools/CoreError.h"
#include "db/IDBQueryResult.h"
#include "db/IDBQuery.h"
#include "DBQueryResult.h"
#include <spdlog/spdlog.h>
#include <cassandra.h>
#include <iostream>

namespace db {

    class Feature;
    using FeaturePtr = std::shared_ptr<Feature>;

    class Feature : public IFeature<IDBQueryResultPtr>, public std::enable_shared_from_this<Feature> {
    public:
        Feature(CassFuture* future, const IDBQueryPtr& query);

        Feature(CassFuture* future, void(*callback)(const IFeaturePtr<IDBQueryResultPtr>&, void*), const IDBQueryPtr& query);

        ~Feature() override;

        bool is_ready() const override;

        void wait() override;

        void cancel() override;

        IDBQueryResultPtr& get_result() override;

        void set_callback(void(*callback)(const IFeaturePtr<IDBQueryResultPtr>&, void*)) override;

        bool has_error() const override;

        IErrorPtr error() const override;

        bool is_canceled() const override;

        bool set_query(const IDBQueryPtr& query);

    private:
        CassFuture* future_;
        void(*callback_)(const IFeaturePtr<IDBQueryResultPtr>&, void*) = nullptr;
        IDBQueryResultPtr res_feat_ = nullptr;
        IErrorPtr error_ = nullptr;
        IDBQueryPtr query_ = nullptr;
    };

}


#endif //BITOCEN_FEATURE_H

//
// Created by Константин Беляков on 01.12.2024.
//

#include "Feature.h"

namespace db {


    Feature::Feature(CassFuture* future, const IDBQueryPtr& query) : future_(future), query_(query) {}

    Feature::Feature(CassFuture* future, void(*callback)(const IFeaturePtr<IDBQueryResultPtr>&, void*), const IDBQueryPtr& query) : future_(future), callback_(callback), query_(query) {
        callback_ = callback;
    }

    Feature::~Feature() {
        spdlog::trace("[db] Feature: Destroy");
        cass_future_free(future_);
    }

    bool Feature::is_ready() const {
        return true;
    }

    void Feature::wait() {
        if (cass_future_error_code(future_) == CASS_OK) {
            const CassResult* result = cass_future_get_result(future_);

            res_feat_ = std::make_shared<DBQueryResult>(result);
            if (callback_ != nullptr) {
                callback_(shared_from_this(), nullptr);
            } else {
                spdlog::warn("[db] Feature: callback_func is nullptr");
            }
        } else {
            const char* error_message;
            size_t error_message_length;
            cass_future_error_message(future_, &error_message, &error_message_length);
            spdlog::error("[db] Feature: Failed to store message! Error: {}", std::string(error_message, error_message_length));
            error_ = std::make_shared<CoreError>(std::string(error_message, error_message_length));
            callback_(shared_from_this(), nullptr);
        }
    }

    void Feature::cancel() {

    }

    IDBQueryResultPtr& Feature::get_result() {
        res_feat_->set_query(query_);
        return res_feat_;
    }

    void Feature::set_callback(void(*callback)(const IFeaturePtr<IDBQueryResultPtr>&, void*)) {
        callback_ = callback;
    }

    bool Feature::has_error() const {
        return error_ != nullptr;
    }

    IErrorPtr Feature::error() const {
        return error_;
    }

    bool Feature::is_canceled() const {
        return false;
    }

    bool Feature::set_query(const IDBQueryPtr& query) {
        query_ = query;
        return true;
    }

}
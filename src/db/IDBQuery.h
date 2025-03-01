//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBQUERY_H
#define BITOCEN_IDBQUERY_H

#include <memory>
#include <string>

namespace db {

    using UINT8VECPtr = std::shared_ptr<std::vector<uint8_t>>;

    class DBQueryParam {
    public:

        enum class ParameterType {
            DEFAULT,
            STRING,
            INT,
            LONGLONG,
            FLOAT,
            BOOL,
            UINT8VEC,
        };

        using ParamType = std::variant<std::string, int, float, bool, UINT8VECPtr, long long>;

        DBQueryParam() : type_(ParameterType::DEFAULT) {}
        DBQueryParam(const std::string& str_value) : value_(str_value), type_(ParameterType::STRING) {}
        DBQueryParam(int int_value) : value_(int_value), type_(ParameterType::INT) {}
        DBQueryParam(long long long_long_value) : value_(long_long_value), type_(ParameterType::LONGLONG) {}
        DBQueryParam(float float_value) : value_(float_value), type_(ParameterType::FLOAT) {}
        DBQueryParam(bool bool_value) : value_(bool_value), type_(ParameterType::BOOL) {}
        DBQueryParam(const UINT8VECPtr& uint_8_vec) : value_(uint_8_vec), type_(ParameterType::UINT8VEC) {}

        // Получение значения параметра в зависимости от типа
        template<typename T>
        T get_value() const {
            return std::get<T>(value_);
        }

        // Получение строкового представления типа
        [[nodiscard]] ParameterType get_type() const {
            return type_;
        }

    private:
        ParameterType type_;
        ParamType value_;
    };

    class IDBQuery;
    using IDBQueryPtr = std::shared_ptr<IDBQuery>;

    class IDBQuery {
    public:

        virtual ~IDBQuery() = default;

        virtual std::string get_string_query() = 0;

        virtual bool from_string(const std::string& query) = 0;

        virtual size_t get_num_parameters() = 0;

        virtual std::vector<size_t> get_params_indexes() = 0;

        virtual DBQueryParam get_param(size_t index) = 0;

        virtual bool set_param(size_t index, const DBQueryParam& param) = 0;


    };

}

#endif //BITOCEN_IDBQUERY_H

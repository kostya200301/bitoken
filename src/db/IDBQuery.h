//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IDBQUERY_H
#define BITOCEN_IDBQUERY_H

#include <memory>
#include <string>

namespace db {

    class DBQueryParam {
    public:

        enum class ParameterType {
            DEFAULT,
            STRING,
            INT,
            FLOAT,
            BOOL,
            // Добавьте другие типы по мере необходимости
        };

        using ParamType = std::variant<std::string, int, float, bool>;

        DBQueryParam() : type_(ParameterType::DEFAULT) {}
        DBQueryParam(const std::string& str_value) : value_(str_value), type_(ParameterType::STRING) {}
        DBQueryParam(int int_value) : value_(int_value), type_(ParameterType::INT) {}
        DBQueryParam(float float_value) : value_(float_value), type_(ParameterType::FLOAT) {}
        DBQueryParam(bool bool_value) : value_(bool_value), type_(ParameterType::BOOL) {}

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

        virtual DBQueryParam get_param(size_t index) = 0;

        virtual bool set_param(size_t index, const DBQueryParam& param) = 0;


    };

}

#endif //BITOCEN_IDBQUERY_H

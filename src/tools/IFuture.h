//
// Created by Константин Беляков on 01.12.2024.
//

#ifndef BITOCEN_IFUTURE_H
#define BITOCEN_IFUTURE_H

#include <memory>
#include <exception>

#include <memory>
#include <functional>
#include <exception>

// Абстрактный интерфейс для асинхронных операций с результатом типа T
template <typename T>
class IFeature {
public:
    virtual ~IFeature() = default;

    // Метод для проверки, готов ли результат
    virtual bool is_ready() const = 0;

    // Метод для блокировки до завершения асинхронной операции
    virtual void wait() = 0;

    // Метод для отмены асинхронной операции
    virtual void cancel() = 0;

    // Метод для получения результата. Результат передается через ссылку.
    virtual bool get_result(T& result) = 0;

    // Метод для установки колбэка, который будет вызван при завершении операции
    virtual void set_callback(std::function<void(T)> callback) = 0;

    // Метод для проверки, произошла ли ошибка во время выполнения операции
    virtual bool has_error() const = 0;

    // Метод для получения информации об ошибке
    virtual std::exception_ptr error() const = 0;

    // Метод для проверки, была ли отменена операция
    virtual bool is_canceled() const = 0;
};




#endif //BITOCEN_IFUTURE_H

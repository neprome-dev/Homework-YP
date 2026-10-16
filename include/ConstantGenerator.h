#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, который всегда возвращает заданное значение
     */
    class ConstantGenerator : public Generator
    {
    private:
        /**
         * @brief Значение, которое возвращает генератор
         */
        int value_;

    public:
        /**
         * @brief Создать генератор с постоянным значением
         * @param value Значение, которое будет возвращать генератор
         */
        explicit ConstantGenerator(int value) noexcept;

        /**
         * @brief Получить заданное постоянное значение
         * @return Значение, заданное при создании генератора
         */
        int generate() const override;
    };
}

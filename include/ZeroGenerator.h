#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, который всегда возвращает ноль
     */
    class ZeroGenerator : public Generator
    {
    public:
        /**
         * @brief Создать генератор нулевых значений
         */
        ZeroGenerator() = default;

        /**
         * @brief Получить нулевое значение
         * @return Ноль
         */
        int generate() const override;
    };
}

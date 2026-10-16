#pragma once

#include <iostream>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, который считывает значения из входного потока
     */
    class IStreamGenerator : public Generator
    {
    private:
        /**
         * @brief Поток, из которого считываются значения
         */
        std::istream& input_;

    public:
        /**
         * @brief Создать генератор для чтения значений из потока
         * @param input Входной поток
         */
        explicit IStreamGenerator(std::istream& input = std::cin) noexcept;

        /**
         * @brief Считать следующее значение из потока
         * @return Считанное значение
         */
        int generate() const override;
    };
}

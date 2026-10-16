#pragma once

#include <random>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор случайных целых чисел в заданном диапазоне
     */
    class RandomGenerator : public Generator
    {
    private:
        /**
         * @brief Генератор псевдослучайных чисел
         */
        mutable std::mt19937 engine_;

        /**
         * @brief Равномерное распределение случайных целых чисел
         */
        mutable std::uniform_int_distribution<int> distribution_;

    public:
        /**
         * @brief Создать генератор случайных чисел в заданном диапазоне
         * @param minimum Минимальное значение диапазона
         * @param maximum Максимальное значение диапазона
         */
        RandomGenerator(int minimum, int maximum);

        /**
         * @brief Сгенерировать случайное число из заданного диапазона
         * @return Случайное число из замкнутого диапазона
         */
        int generate() const override;
    };
}

#pragma once

#include "Generator.h"

#include <random>

namespace miit::algebra
{
    /**
     * @brief Генератор случайных целых чисел из замкнутого диапазона.
     */
    class RandomGenerator final : public Generator
    {
    private:
        mutable std::mt19937 engine_;
        mutable std::uniform_int_distribution<int> distribution_;

    public:
        RandomGenerator(int minimum, int maximum);
        int generate() const override;
    };
}

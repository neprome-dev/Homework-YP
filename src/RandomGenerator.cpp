#include "RandomGenerator.h"

#include <stdexcept>

namespace miit::algebra
{
    RandomGenerator::RandomGenerator(const int minimum, const int maximum)
        : engine_(std::random_device{}()), distribution_()
    {
        if (minimum > maximum)
        {
            throw std::invalid_argument("Минимум диапазона не может быть больше максимума");
        }

        distribution_ = std::uniform_int_distribution<int>(minimum, maximum);
    }

    int RandomGenerator::generate() const
    {
        return distribution_(engine_);
    }
}

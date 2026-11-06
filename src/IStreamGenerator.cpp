#include <stdexcept>

#include "../include/IStreamGenerator.h"

namespace miit::algebra
{
    IStreamGenerator::IStreamGenerator(std::istream& input)
        : input_(input)
    {
    }

    int IStreamGenerator::generate() const
    {
        int value = 0;
        if (!(input_ >> value))
        {
            throw std::runtime_error("Не удалось прочитать целое число");
        }
        return value;
    }
}

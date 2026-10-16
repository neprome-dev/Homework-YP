#pragma once

#include "Generator.h"

#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Генератор, считывающий целые значения из входного потока.
     */
    class IStreamGenerator final : public Generator
    {
    private:
        std::istream& input_;

    public:
        explicit IStreamGenerator(std::istream& input = std::cin) noexcept;
        int generate() const override;
    };
}

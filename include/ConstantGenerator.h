#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор заданного постоянного значения.
     */
    class ConstantGenerator final : public Generator
    {
    private:
        int value_;

    public:
        explicit ConstantGenerator(int value) noexcept;
        int generate() const override;
    };
}

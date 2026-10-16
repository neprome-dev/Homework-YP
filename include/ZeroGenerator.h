#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор нулевых значений.
     */
    class ZeroGenerator final : public Generator
    {
    public:
        int generate() const override;
    };
}

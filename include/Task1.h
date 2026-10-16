#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Заменяет первое вхождение максимума каждой строки нулём.
     */
    class Task1 final : public Exercise
    {
    private:
        Matrix<int> result_;

    public:
        Task1(Matrix<int>& matrix, const Generator& generator) noexcept;
        Matrix<int>& Solve() override;
    };
}

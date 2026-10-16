#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Вставляет нулевую строку перед строками, начинающимися с числа, кратного трём.
     */
    class Task2 final : public Exercise
    {
    private:
        Matrix<int> result_;

    public:
        Task2(Matrix<int>& matrix, const Generator& generator) noexcept;
        Matrix<int>& Solve() override;
    };
}

#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
    /**
     * @brief Базовый класс задания над целочисленной матрицей.
     */
    class Exercise
    {
    protected:
        Matrix<int>& source_;
        const Generator& generator_;

    public:
        Exercise(Matrix<int>& matrix, const Generator& generator) noexcept;
        virtual ~Exercise();

        /**
         * @brief Заполнить исходную матрицу выбранным генератором.
         */
        void Fill();

        /**
         * @brief Выполнить вариантное преобразование.
         */
        virtual Matrix<int>& Solve() = 0;
    };
}

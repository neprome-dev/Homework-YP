#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Реализация первого задания варианта 22
     */
    class Task1 : public Exercise
    {
    private:
        /**
         * @brief Матрица с результатом первого задания
         */
        Matrix<int> result_;

    public:
        /**
         * @brief Создать объект первого задания варианта 22
         * @param matrix Матрица, над которой будет выполняться задание
         * @param generator Генератор для заполнения матрицы
         */
        Task1(Matrix<int>& matrix, const Generator& generator) noexcept;

        /**
         * @brief Заменить первое вхождение максимума каждой строки нулём
         * @return Матрица после выполнения первого задания
         */
        Matrix<int>& Solve() override;
    };
}

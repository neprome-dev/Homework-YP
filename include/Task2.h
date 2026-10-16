#pragma once

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Реализация второго задания варианта 22
     */
    class Task2 : public Exercise
    {
    private:
        /**
         * @brief Матрица с результатом второго задания
         */
        Matrix<int> result_;

    public:
        /**
         * @brief Создать объект второго задания варианта 22
         * @param matrix Матрица, над которой будет выполняться задание
         * @param generator Генератор для заполнения матрицы
         */
        Task2(Matrix<int>& matrix, const Generator& generator) noexcept;

        /**
         * @brief Вставить нулевую строку перед каждой строкой, первый элемент которой кратен трём
         * @return Матрица после выполнения второго задания
         */
        Matrix<int>& Solve() override;
    };
}

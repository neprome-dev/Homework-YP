#pragma once

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
    /**
     * @brief Базовый класс для заданий, выполняемых над матрицей
     */
    class Exercise
    {
    protected:
        /**
         * @brief Матрица, над которой выполняются задания
         */
        Matrix<int>& source_;

        /**
         * @brief Генератор, используемый для заполнения матрицы
         */
        const Generator& generator_;

    public:
        /**
         * @brief Создать объект задания для указанной матрицы
         * @param matrix Матрица, над которой будет выполняться задание
         * @param generator Генератор для заполнения матрицы
         */
        Exercise(Matrix<int>& matrix, const Generator& generator) noexcept;

        /**
         * @brief Уничтожить объект задания
         */
        virtual ~Exercise() = default;

        /**
         * @brief Заполнить матрицу с помощью выбранного генератора
         */
        void Fill();

        /**
         * @brief Выполнить задание
         * @return Матрица с результатом задания
         */
        virtual Matrix<int>& Solve() = 0;
    };
}

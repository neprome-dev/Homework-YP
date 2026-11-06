#pragma once

#include <cstddef>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Класс для работы с прямоугольной матрицей
     * @tparam T Тип элемента матрицы
     */
    template <typename T>
    class Matrix
    {
    private:
        /**
         * @brief Данные матрицы
         */
        std::vector<std::vector<T>> data_;

        /**
         * @brief Количество столбцов матрицы
         */
        std::size_t columns_ = 0U;

    public:
        /**
         * @brief Создать пустую матрицу
         */
        Matrix() = default;

        /**
         * @brief Создать матрицу заданного размера
         * @param rows Количество строк
         * @param columns Количество столбцов
         */
        Matrix(const std::size_t rows, const std::size_t columns)
            : data_(rows, std::vector<T>(columns)), columns_(columns)
        {
        }

        /**
         * @brief Создать копию другой матрицы
         * @param other Матрица, которую нужно скопировать
         */
        Matrix(const Matrix& other) = default;

        /**
         * @brief Создать матрицу, переместив данные из другого объекта
         * @param other Матрица, из которой нужно переместить данные
         */
        Matrix(Matrix&& other) noexcept
            : data_(std::move(other.data_)), columns_(other.columns_)
        {
            other.data_.clear();
            other.columns_ = 0U;
        }

        /**
         * @brief Присвоить текущей матрице копию другой матрицы
         * @param other Матрица, которую нужно скопировать
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator=(const Matrix& other) = default;

        /**
         * @brief Переместить данные другой матрицы в текущую
         * @param other Матрица, из которой нужно переместить данные
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator=(Matrix&& other) noexcept
        {
            if (this != &other)
            {
                data_ = std::move(other.data_);
                columns_ = other.columns_;
                other.data_.clear();
                other.columns_ = 0U;
            }
            return *this;
        }

        /**
         * @brief Уничтожить матрицу
         */
        ~Matrix() = default;

        /**
         * @brief Получить количество строк матрицы
         * @return Количество строк
         */
        std::size_t rowsCount() const noexcept
        {
            return data_.size();
        }

        /**
         * @brief Получить количество столбцов матрицы
         * @return Количество столбцов
         */
        std::size_t columnsCount() const noexcept
        {
            return columns_;
        }

        /**
         * @brief Проверить, не содержит ли матрица элементов
         * @return true, если в матрице нет элементов, иначе false
         */
        bool empty() const noexcept
        {
            return rowsCount() == 0U || columnsCount() == 0U;
        }

        /**
         * @brief Получить строку матрицы по индексу
         * @param row Индекс строки
         * @return Ссылка на выбранную строку
         */
        std::vector<T>& operator[](const std::size_t row)
        {
            if (row >= rowsCount())
            {
                throw std::out_of_range("Индекс строки вне диапазона");
            }
            return data_[row];
        }

        /**
         * @brief Получить строку неизменяемой матрицы по индексу
         * @param row Индекс строки
         * @return Константная ссылка на выбранную строку
         */
        const std::vector<T>& operator[](const std::size_t row) const
        {
            if (row >= rowsCount())
            {
                throw std::out_of_range("Индекс строки вне диапазона");
            }
            return data_[row];
        }

        /**
         * @brief Проверить матрицы на равенство
         * @param other Матрица для сравнения
         * @return true, если матрицы равны, иначе false
         */
        bool operator==(const Matrix& other) const
        {
            if (rowsCount() != other.rowsCount() || columnsCount() != other.columnsCount())
            {
                return false;
            }

            for (std::size_t row = 0U; row < rowsCount(); ++row)
            {
                for (std::size_t column = 0U; column < columnsCount(); ++column)
                {
                    if (data_[row][column] != other.data_[row][column])
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        /**
         * @brief Проверить матрицы на неравенство
         * @param other Матрица для сравнения
         * @return true, если матрицы различаются, иначе false
         */
        bool operator!=(const Matrix& other) const
        {
            return !(*this == other);
        }

        /**
         * @brief Заполнить матрицу значениями из генератора
         * @param generator Генератор значений
         */
        void fill(const Generator& generator)
        {
            for (std::size_t row = 0U; row < rowsCount(); ++row)
            {
                for (std::size_t column = 0U; column < columnsCount(); ++column)
                {
                    data_[row][column] = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Получить строковое представление матрицы
         * @return Строка с элементами матрицы
         */
        std::string toString() const
        {
            std::ostringstream output;

            for (std::size_t row = 0U; row < rowsCount(); ++row)
            {
                for (std::size_t column = 0U; column < columnsCount(); ++column)
                {
                    if (column != 0U)
                    {
                        output << ' ';
                    }
                    output << data_[row][column];
                }

                if (row + 1U != rowsCount())
                {
                    output << '\n';
                }
            }

            return output.str();
        }
    };

    /**
     * @brief Вывести матрицу в поток
     * @tparam T Тип элемента матрицы
     * @param output Поток для вывода
     * @param matrix Матрица, которую нужно вывести
     * @return Поток после вывода матрицы
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix)
    {
        return output << matrix.toString();
    }

    /**
     * @brief Считать элементы матрицы из потока
     * @tparam T Тип элемента матрицы
     * @param input Поток для чтения
     * @param matrix Матрица, которую нужно заполнить
     * @return Поток после чтения матрицы
     */
    template <typename T>
    std::istream& operator>>(std::istream& input, Matrix<T>& matrix)
    {
        for (std::size_t row = 0U; row < matrix.rowsCount(); ++row)
        {
            for (std::size_t column = 0U; column < matrix.columnsCount(); ++column)
            {
                if (!(input >> matrix[row][column]))
                {
                    return input;
                }
            }
        }
        return input;
    }
}

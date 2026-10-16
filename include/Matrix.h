#pragma once

#include "Generator.h"

#include <cstddef>
#include <initializer_list>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace miit::algebra
{
    /**
     * @brief Прямоугольная двумерная матрица.
     * @tparam T Тип элемента матрицы.
     */
    template <typename T = int>
    class Matrix
    {
    private:
        std::vector<std::vector<T>> data_;
        std::size_t columns_ = 0U;

        void validateRectangular() const
        {
            for (const auto& row : data_)
            {
                if (row.size() != columns_)
                {
                    throw std::invalid_argument("Строки матрицы должны иметь одинаковую длину");
                }
            }
        }

    public:
        Matrix() = default;

        Matrix(std::size_t rows, std::size_t columns, const T& initialValue = T{})
            : data_(rows, std::vector<T>(columns, initialValue)), columns_(columns)
        {
        }

        explicit Matrix(std::vector<std::vector<T>> values)
            : data_(std::move(values)), columns_(data_.empty() ? 0U : data_.front().size())
        {
            validateRectangular();
        }

        Matrix(std::initializer_list<std::initializer_list<T>> values)
        {
            data_.reserve(values.size());
            for (const auto& row : values)
            {
                data_.emplace_back(row);
            }
            columns_ = data_.empty() ? 0U : data_.front().size();
            validateRectangular();
        }

        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) noexcept = default;
        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) noexcept = default;
        ~Matrix() = default;

        std::size_t rowsCount() const noexcept
        {
            return data_.size();
        }

        std::size_t columnsCount() const noexcept
        {
            return columns_;
        }

        bool empty() const noexcept
        {
            return rowsCount() == 0U || columnsCount() == 0U;
        }

        std::vector<T>& operator[](std::size_t row)
        {
            return data_.at(row);
        }

        const std::vector<T>& operator[](std::size_t row) const
        {
            return data_.at(row);
        }

        T& operator()(std::size_t row, std::size_t column)
        {
            return data_.at(row).at(column);
        }

        const T& operator()(std::size_t row, std::size_t column) const
        {
            return data_.at(row).at(column);
        }

        bool operator==(const Matrix& other) const
        {
            return columns_ == other.columns_ && data_ == other.data_;
        }

        bool operator!=(const Matrix& other) const
        {
            return !(*this == other);
        }

        /**
         * @brief Заполнить матрицу значениями указанного генератора.
         */
        void fill(const Generator& generator)
        {
            for (auto& row : data_)
            {
                for (auto& value : row)
                {
                    value = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Вставить строку перед указанной позицией.
         */
        void insertRow(std::size_t index, const std::vector<T>& row)
        {
            if (index > rowsCount())
            {
                throw std::out_of_range("Индекс вставки строки вне диапазона");
            }

            if (row.size() != columnsCount() && (columnsCount() != 0U || !data_.empty()))
            {
                throw std::invalid_argument("Размер вставляемой строки не совпадает с матрицей");
            }

            if (data_.empty() && columnsCount() == 0U)
            {
                columns_ = row.size();
            }

            data_.insert(data_.begin() + static_cast<std::ptrdiff_t>(index), row);
        }

        /**
         * @brief Получить строковое представление матрицы.
         */
        std::string toString() const
        {
            std::ostringstream output;
            output << *this;
            return output.str();
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& output, const Matrix<U>& matrix);

        template <typename U>
        friend std::istream& operator>>(std::istream& input, Matrix<U>& matrix);
    };

    template <typename U>
    std::ostream& operator<<(std::ostream& output, const Matrix<U>& matrix)
    {
        for (std::size_t row = 0; row < matrix.rowsCount(); ++row)
        {
            for (std::size_t column = 0; column < matrix.columnsCount(); ++column)
            {
                if (column != 0U)
                {
                    output << ' ';
                }
                output << matrix.data_[row][column];
            }

            if (row + 1U != matrix.rowsCount())
            {
                output << '\n';
            }
        }
        return output;
    }

    template <typename U>
    std::istream& operator>>(std::istream& input, Matrix<U>& matrix)
    {
        for (auto& row : matrix.data_)
        {
            for (auto& value : row)
            {
                if (!(input >> value))
                {
                    return input;
                }
            }
        }
        return input;
    }
}

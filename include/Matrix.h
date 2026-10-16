#pragma once

#include <cstddef>
#include <initializer_list>
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
    template <typename T = int>
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

        /**
         * @brief Проверить, что все строки матрицы имеют одинаковую длину
         */
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
        /**
         * @brief Создать пустую матрицу
         */
        Matrix() = default;

        /**
         * @brief Создать матрицу заданного размера
         * @param rows Количество строк
         * @param columns Количество столбцов
         * @param initialValue Начальное значение каждого элемента
         */
        Matrix(std::size_t rows, std::size_t columns, const T& initialValue = T{})
            : data_(rows, std::vector<T>(columns, initialValue)), columns_(columns)
        {
        }

        /**
         * @brief Создать матрицу из двумерного вектора
         * @param values Значения элементов матрицы
         */
        explicit Matrix(std::vector<std::vector<T>> values)
            : data_(std::move(values)), columns_(data_.empty() ? 0U : data_.front().size())
        {
            validateRectangular();
        }

        /**
         * @brief Создать матрицу из списка строк
         * @param values Значения элементов матрицы
         */
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
        std::vector<T>& operator[](std::size_t row)
        {
            return data_.at(row);
        }

        /**
         * @brief Получить строку неизменяемой матрицы по индексу
         * @param row Индекс строки
         * @return Константная ссылка на выбранную строку
         */
        const std::vector<T>& operator[](std::size_t row) const
        {
            return data_.at(row);
        }

        /**
         * @brief Получить элемент матрицы по индексам
         * @param row Индекс строки
         * @param column Индекс столбца
         * @return Ссылка на выбранный элемент
         */
        T& operator()(std::size_t row, std::size_t column)
        {
            return data_.at(row).at(column);
        }

        /**
         * @brief Получить элемент неизменяемой матрицы по индексам
         * @param row Индекс строки
         * @param column Индекс столбца
         * @return Константная ссылка на выбранный элемент
         */
        const T& operator()(std::size_t row, std::size_t column) const
        {
            return data_.at(row).at(column);
        }

        /**
         * @brief Проверить матрицы на равенство
         * @param other Матрица для сравнения
         * @return true, если матрицы равны, иначе false
         */
        bool operator==(const Matrix& other) const
        {
            return columns_ == other.columns_ && data_ == other.data_;
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
            for (auto& row : data_)
            {
                for (auto& value : row)
                {
                    value = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Вставить строку перед указанной позицией
         * @param index Индекс позиции для вставки
         * @param row Вставляемая строка
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
         * @brief Получить строковое представление матрицы
         * @return Строка с элементами матрицы
         */
        std::string toString() const
        {
            std::ostringstream output;
            output << *this;
            return output.str();
        }

        /**
         * @brief Вывести матрицу в поток
         * @tparam U Тип элемента матрицы
         * @param output Поток для вывода
         * @param matrix Матрица, которую нужно вывести
         * @return Поток после вывода матрицы
         */
        template <typename U>
        friend std::ostream& operator<<(std::ostream& output, const Matrix<U>& matrix);

        /**
         * @brief Считать элементы матрицы из потока
         * @tparam U Тип элемента матрицы
         * @param input Поток для чтения
         * @param matrix Матрица, которую нужно заполнить
         * @return Поток после чтения матрицы
         */
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

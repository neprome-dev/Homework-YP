#include "../include/Task2.h"

namespace miit::algebra
{
    Task2::Task2(Matrix<int>& matrix, const Generator& generator)
        : Exercise(matrix, generator)
    {
    }

    Matrix<int>& Task2::Solve()
    {
        if (source_.columnsCount() == 0U)
        {
            result_ = source_;
            return result_;
        }

        std::size_t resultRows = source_.rowsCount();

        for (std::size_t row = 0U; row < source_.rowsCount(); ++row)
        {
            if (source_[row][0] % 3 == 0)
            {
                ++resultRows;
            }
        }

        result_ = Matrix<int>(resultRows, source_.columnsCount());
        std::size_t resultRow = 0U;

        for (std::size_t row = 0U; row < source_.rowsCount(); ++row)
        {
            if (source_[row][0] % 3 == 0)
            {
                ++resultRow;
            }

            for (std::size_t column = 0U; column < source_.columnsCount(); ++column)
            {
                result_[resultRow][column] = source_[row][column];
            }

            ++resultRow;
        }

        return result_;
    }
}

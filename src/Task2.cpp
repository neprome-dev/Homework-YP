#include "../include/Task2.h"

#include <vector>

namespace miit::algebra
{
    Task2::Task2(Matrix<int>& matrix, const Generator& generator) noexcept
        : Exercise(matrix, generator)
    {
    }

    Matrix<int>& Task2::Solve()
    {
        result_ = source_;

        if (result_.columnsCount() == 0U)
        {
            return result_;
        }

        const std::vector<int> zeroRow(result_.columnsCount(), 0);
        const std::size_t originalRows = result_.rowsCount();

        // Обход снизу вверх сохраняет индексы ещё не обработанных исходных строк.
        for (std::size_t row = originalRows; row-- > 0U;)
        {
            if (result_[row][0] % 3 == 0)
            {
                result_.insertRow(row, zeroRow);
            }
        }

        return result_;
    }
}

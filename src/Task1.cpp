#include "../include/Task1.h"

namespace miit::algebra
{
    Task1::Task1(Matrix<int>& matrix, const Generator& generator)
        : Exercise(matrix, generator)
    {
    }

    Matrix<int>& Task1::Solve()
    {
        result_ = source_;

        if (result_.columnsCount() == 0U)
        {
            return result_;
        }

        for (std::size_t row = 0; row < result_.rowsCount(); ++row)
        {
            std::size_t maximumColumn = 0U;

            for (std::size_t column = 1U; column < result_.columnsCount(); ++column)
            {
                if (result_[row][column] > result_[row][maximumColumn])
                {
                    maximumColumn = column;
                }
            }

            result_[row][maximumColumn] = 0;
        }

        return result_;
    }
}

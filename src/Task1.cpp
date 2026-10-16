#include "Task1.h"

#include <algorithm>

namespace miit::algebra
{
    Task1::Task1(Matrix<int>& matrix, const Generator& generator) noexcept
        : Exercise(matrix, generator)
    {
    }

    Matrix<int>& Task1::Solve()
    {
        result_ = source_;

        for (std::size_t row = 0; row < result_.rowsCount(); ++row)
        {
            if (result_[row].empty())
            {
                continue;
            }

            const auto maximum = std::max_element(result_[row].begin(), result_[row].end());
            *maximum = 0;
        }

        return result_;
    }
}

#include "../include/Exercise.h"

namespace miit::algebra
{
    Exercise::Exercise(Matrix<int>& matrix, const Generator& generator) noexcept
        : source_(matrix), generator_(generator)
    {
    }

    void Exercise::Fill()
    {
        source_.fill(generator_);
    }
}

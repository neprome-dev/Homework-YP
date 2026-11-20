#include "../include/Exercise.h"

namespace miit::algebra
{
    Exercise::Exercise(Matrix<int>& matrix, const Generator& generator)
        : source_(matrix)
    {
        source_.fill(generator);
    }
}

#include "../include/ClassMathHelper.h"

#include <cmath>

const double MathHelper::defaultEpsilon = 1e-9;

bool MathHelper::isEqual(const double left, const double right, const double epsilon)
{
	return fabs(left - right) < epsilon;
}

bool MathHelper::isEqual(const double left, const double right)
{
	return isEqual(left, right, defaultEpsilon);
}

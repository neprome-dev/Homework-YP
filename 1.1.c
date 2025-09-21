#include <stdio.h>
#include <math.h>

/**
* Рассчитывает значение функции A
* @param x - значение параметра x
* @param y - значение параметра y
* @param z - значение параметра z
* @return значение A
*/
double getA(const double x, const double y, const double z);

/**
* Рассчитывает значение функции B
* @param x - значение параметра x
* @param y - значение параметра y
* @param z - значение параметра z
* @return значение B
*/
double getB(const double x, const double y, const double z);

/**
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/

int main()
{
	const double x = 0.5;
	const double y = 1.7;
	const double z = 0.44;

	printf("A = %.6f\n", getA(x, y, z));
	printf("B = %.6f\n", getB(x, y, z));
	return 0;
}

double getA(const double x, const double y, const double z)
{
	return exp(-y * z) * sin(x * z - y) - sqrt(fabs(y * z + x));
}

double getB(const double x, const double y, const double z)
{
	double a = getA(x, y, z);
	return y * sin(a * z * z * cos(2 * z)) - 1.0;
}

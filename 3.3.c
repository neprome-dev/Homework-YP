#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

/**
* @brief Вычисляет cos(x) с использованием встроенной функции
* @param x значение аргумента
* @return Значение cos(x)
*/
double functionCos(const double x);

/**
* @brief Вычисляет сумму ряда с заданной точностью
* @param x значение аргумента
* @return Сумма ряда для cos(x)
*/
double getSumSeries(const double x);

/**
* @brief Вычисляет следующий элемент ряда по рекуррентной формуле
* @param n номер текущего элемента
* @param x значение аргумента
* @param prevElement предыдущий элемент ряда
* @return Следующий элемент ряда
*/
double getNextElement(const int n, const double x, const double prevElement);

/**
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/
int main(void)
{
	system("chcp 1251");

	printf("%-15s%-20s%-20s\n", "x", "cos(x)", "S(x)");
	printf("%-15s%-20s%-20s\n", "-----", "--------", "--------");
	double x = 0.1;
	double end = 1.0;
	double step = 0.1;

	for (x; x <= end + DBL_EPSILON; x += step) {
		printf("%-15.4lf%-20.6lf%-20.6lf\n", x, functionCos(x), getSumSeries(x));
	}
  
	return 0;
}

double functionCos(const double x)
{
	return cos(x);
}

double getSumSeries(const double x)
{
	double sum = 1.0;
	double element = 1.0;
	double E = 1e-4;
	int n = 1;

	while (fabs(element) > E) {
		element = getNextElement(n, x, element);
		sum += element;
		n++;
	}

	return sum;
}

double getNextElement(const int n, const double x, const double prevElement)
{
	return prevElement * (-x * x) / ((2 * n - 1) * (2 * n));
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
* @brief Считывает значение, введённое с клавиатуры, с проверкой ввода
* @return Считанное значение
*/
double defValid(void);

/**
* @brief Проверяет, что x и y не равны друг другу
* @param x первое число
* @param y второе число
* @return true, если числа не равны, false если равны
*/
bool isNotEqual(const double x, const double y);

/**
* @brief Вычисляет половину суммы двух чисел
* @param x первое число
* @param y второе число
* @return Половина суммы (x + y) / 2
*/
double getHalfSum(const double x, const double y);

/**
* @brief Вычисляет удвоенное произведение двух чисел
* @param x первое число
* @param y второе число
* @return Удвоенное произведение 2 * x * y
*/
double getDoubleProduct(const double x, const double y);

/**
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/
int main(void)
{
	system("chcp 1251");

	printf("Введите число x: ");
	double x = defValid();

	printf("\nВведите число y: ");
	double y = defValid();

	if (!isNotEqual(x, y)) {
		fprintf(stderr, "x и y должны быть не равны\n");
		exit(1);
	}

	double sum = getHalfSum(x, y);
	double product = getDoubleProduct(x, y);

	if (x < y) {
		x = sum;
		y = product;
	} else {
		x = product;
		y = sum;
	}

	printf("x = %.6lf\n", x);
	printf("y = %.6lf\n", y);

	return 0;
}

double defValid(void)
{
	double valid = 0;
	if (!scanf_s("%lf", &valid)) {
		fprintf(stderr, "Некорректный ввод\n");
		exit(1);
	}
	return valid;
}

bool isNotEqual(const double x, const double y)
{
	return x != y;
}

double getHalfSum(const double x, const double y)
{
	return (x + y) / 2;
}

double getDoubleProduct(const double x, const double y)
{
	return 2 * x * y;
}

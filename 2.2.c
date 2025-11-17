#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

/**
* @brief is_zero проверяет, является ли число нулём
* @param number число
* @return возвращает true, если число является нулём и false, если не является нулём
*/
bool is_zero(const double number);
/*
* @brief input принимает на вход значение double, вводимое пользователем
* @return возвращает значение, введеное пользователем
*/
double input(void);

/*
* @brief get_y считает возвращает значение y, исходя из x
* @param x параметр x
* @param a параметр a
* @return возвращает значение y
*/
double get_y(const double x, const double a);

/*
* @brief first_operation считает значение y при x < 1.34
* @param x параметр x
* @return возвращает значение y
*/
double first_operation(const double x);

/*
* @brief first_operation считает значение y при x > 1.4
* @param x параметр x
* @return возвращает значение y
*/
double second_operation(const double x, const double a);

/**
* @brief is_define проверяет подходит ли параметр x
* @param x параметр x
* @return true, если x подходит и false, если не подходит
*/
bool is_define(const double x);

/*
* @brief main принимает на вход значение x и выводит y
* @return возвращает 0 в случае успеха
*/
int main(void) {

	double a = 1.65;

	puts("Enter the x:");

	double x = input();

	if (!is_define(x)) {

		puts("Your input is uncorrected");

		return 1;
	}

	printf("y = %f", get_y(x, a));

	return 0;
}

double input(void) {

	double number = 0;;

	if (scanf_s("%lf", &number) != 1) {

		puts("Your input is uncorrected");

		exit(EXIT_FAILURE);
	}

	return number;
}

double first_operation(const double x) {

	if (is_zero(x))
	{
		puts("Your inpur is uncorrected");
		exit(EXIT_FAILURE);
	}

	return 3.14 * pow(x, 2) - 7 / pow(x, 2);
}

double second_operation(const double x, const double a) {


	return log(x + 7 * sqrt(x + a));
}

double get_y(const double x, const double a) {

	if (x < 1.34 + DBL_EPSILON) {

		return first_operation(x);
	}
	else if(x >= 1.4 + DBL_EPSILON){
		
		return second_operation(x, a);
	}
}

bool is_define(const double x) {

	return x < 1.34 + DBL_EPSILON || x >= 1.4 + DBL_EPSILON;
}

bool is_zero(const double number)
{
	return fabs(number) < DBL_EPSILON;
}

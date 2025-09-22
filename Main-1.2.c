#include <stdio.h>
#include <math.h>

/*
* @brief Считывает с клавиатуры значение первого числа
* @return Возвращает значение первого числа
*/
double read_a(void);

/*
* @brief Считывает с клавиатуры значение второго числа
* @return Возвращает значение второго числа
*/
double read_b(void);

/*
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/

int main(void)
{
	const double a = read_a();
	const double b = read_b();
	const double summa = a+b;
	printf("\nA+B = %.2f\n", summa);
	const double difference = fabs(a-b);
	printf("|A-B| = %.2f\n", difference);
	const double proizvedenie = a*b;
	printf("A*B = %.2f\n", proizvedenie);
	const double div_ab = a/b;
	printf("A/B = %.2f\n", div_ab);
	const double div_ba = b/a;
	printf("B/A = %.2f\n\n\n\n", div_ba);
	return 0;
}

double read_a(void)
{
	printf("Enter first number\n");
	double a;
	scanf_s("%lf", &a);
	return a;
}
double read_b(void)
{
	printf("Enter second number\n");
	double b;
	scanf_s("%lf", &b);
	return b;
}

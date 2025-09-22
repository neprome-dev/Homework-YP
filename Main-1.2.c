#include <stdio.h>
#include <math.h>

/*
* @brief Считывает с клавиатуры значение введенного числа
* @return Возвращает значение числа
*/
double read(void);

/*
* @brief Высчитывает сумму полученных чисел
* @param a - первое полученное число
* @param b - второе полученное число
* @return Сумму введенных двух чисел
*/
double sum(const double a, const double b);

/*
* @brief Высчитывает разность полученных чисел
* @param a - первое полученное число
* @param b - второе полученное число
* @return Разность введенных двух чисел
*/
double diff(const double a, const double b);

/*
* @brief Высчитывает произведение полученных чисел
* @param a - первое полученное число
* @param b - второе полученное число
* @return Произведение введенных двух чисел
*/
double multiply(const double a, const double b);

/*
* @brief Высчитывает частное полученных чисел (a делится на b)
* @param a - первое полученное число
* @param b - второе полученное число
* @return частное введенных двух чисел
*/
double divide_ab(const double a, const double b);

/*
* @brief Высчитывает частное полученных чисел (b делится на a)
* @param a - первое полученное число
* @param b - второе полученное число
* @return частное введенных двух чисел
*/
double divide_ba(const double a, const double b);

/*
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/
int main(void)
{
	printf("Enter first number\n");
	const double a = read();
	printf("Enter second number\n");
	const double b = read();
	const double summa = sum(a, b);
	printf("\nA+B = %.2f\n", summa);
	const double difference = diff(a, b);
	printf("|A-B| = %.2f\n", difference);
	const double proizvedenie = multiply(a, b);
	printf("A*B = %.2f\n", proizvedenie);
	const double div_ab = divide_ab(a, b);
	printf("A/B = %.2f\n", div_ab);
	const double div_ba = divide_ba(a, b);
	printf("B/A = %.2f\n\n\n\n", div_ba);
	return 0;
}

double read(void)
{
	double num;
	scanf_s("%lf", &num);
	return num;
}

double sum(const double a, const double b)
{
	double summa = a + b;
	return summa;
}

double diff(const double a, const double b)
{
	double difference = fabs(a - b);
	return difference;
}

double multiply(const double a, const double b)
{
	double proizvedenie = a * b;
	return proizvedenie;
}

double divide_ab(const double a, const double b)
{
	double div = a / b;
	return div;
}
double divide_ba(const double a, const double b)
{
	double div = b / a;
	return div;
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

/**
* @brief Вычисляет значение функции в точке
* @param x точка
* @return Вычисленное значение
*/
double function(const double x);

/**
* @brief Вычисляет сумму ряда с заданной точностью
* @param e точность расчета
* @param x значение параметра x
* @return Вычисленное значение суммы
*/
double defSummE(const double e, const double x);

/**
* @brief Считывает значение с клавиатуры с проверкой ввода
* @return Считанное значение
*/
double defValid(void);

/**
* @brief Вычисляет коэффициент рекуррентного выражения
* @param n текущий номер члена
* @param x значение параметра x
* @return Коэффициент для рекуррентной формулы
*/
double getRecurent(const int n, const double x);

/**
* @brief Проверяет, что число положительно
* @param input проверяемое значение
*/
void CheckValue(const double input);

/**
* @brief Проверяет корректность интервала
* @param start начало интервала
* @param end конец интервала
*/
void checkEndStart(const double start, const double end);

/**
* @brief Проверяет, что шаг положительный
* @param step значение шага
*/
void checkStep(const double step);

/**
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/
int main(void)
{
 system("chcp 1251");

 printf("Введите число e: ");
 double e = defValid();
 CheckValue(e);

 printf("Введите начальное значение: ");
 double start = defValid();
 printf("Введите конечное значение: ");
 double end = defValid();
 checkEndStart(start, end);

 printf("Введите шаг: ");
 double step = defValid();
 checkStep(step);

 printf("%-10s%-25s%-10s\n", "x", "f(x)", "Summ(x)");
 for (double x = start; x <= end + DBL_EPSILON; x += step)
 {
  {
   printf("%-10.2lf%-25.6lf%-10.6lf\n", x, function(x), defSummE(e, x));
  }
 }

 return 0;
}

double function(const double x)
{
 return cos(x);
}

double defValid(void)
{
 double valid = 0;
 if (!scanf_s("%lf", &valid))
 {
  printf("Error\n");
  exit(1);
 }
 return valid;
}

void CheckValue(const double input)
{
 if (!(input > DBL_EPSILON))
 {
  printf("Error\n");
  exit(1);
 }
}

double defSummE(const double e, const double x)
{
 double current = 1.0;
 double result = 0;
 for (int n = 1; fabs(current) > e; n++)
 {
  result += current;
  current *= getRecurent(n, x);
 }
 return result;
}

void checkEndStart(const double start, const double end)
{
 if (!(fabs(start - end) < DBL_EPSILON)
 {
  printf("Error\n Значения не должны совпадать или значение начала не может быть больше значения конца\n");
  exit(1);
 }
}

void checkStep(const double step)
{
 if (step < DBL_EPSILON)
 {
  printf("Error\n Шаг должен быть больше 0\n");
  exit(1);
 }
}

double getRecurent(const int n, const double x)
{
 return (-x * x) / ((2 * n - 1) * (2 * n));
}

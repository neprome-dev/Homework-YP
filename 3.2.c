#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

/**
* @brief dinput считывает данные типа int, вводимые пользователем
* @return возвращает значение, введённое пользователем
*/
int dinput(void);

/**
* @brief finput считывает значения типа double, вводимые пользователем
* @return возвращает значение, введённое пользователем
*/
double finput(void);

/**
* @brief get_next_element считает следующий элемент последовательности
* @param last_element последний элемент последовательности a_{k-1}
* @param k номер нового элемента k
* @return возвращает следующий элемент последовательности a_k
*/
double get_next_element(const double last_element, const int k);

/**
* @brief get_summ считает сумму для первых n элементов
* @param n параметр n
* @return возвращает сумму первых n элементов
*/
double get_summ(const int n);

/**
* @brief get_summ_e считает сумму элементов, модуль которых >= e
* @param e параметр e
* @return возвращает сумму элементов последовательности, модуль которых не меньше e
*/
double get_summ_e(const double e);

/**
* @brief is_positive проверяет положителен ли n
* @param n параметр n
* @return возвращает true, если n положителен и false, если равен или меньше 0
*/
bool is_positive(const int n);

/**
* @brief is_positive_d проверяет положителен ли e
* @param e параметр e
* @return возвращает true, если e положителен и false, если равен или меньше 0
*/
bool is_positive_d(const double e);

/**
* @brief main выводит значения сумм
* @return возвращает 0 в случае успеха
*/
int main(void)
{
    puts("Enter n:");
    int n = dinput();

    puts("Enter e:");
    double e = finput();

    double sum_first_n_terms  = get_summ(n);
    double sum_above_threshold  = get_summ_e(sum_above_threshold);

    printf("Sum of first n terms: %lf\n", sum_first_n_terms);
    printf("Sum of terms with |a_k| >= e: %lf\n", sum_above_threshold);

    return 0;
}

double get_summ(const int n)
{
    double last_element = -1.0;
    double summ = last_element;

    for (int k = 2; k <= n; ++k)
    {
        last_element = get_next_element(last_element, k);
        summ += last_element;
    }

    return summ;
}

double get_next_element(const double last_element, const int k)
{
    return last_element / (-pow(k, 2));
}

double get_summ_e(const double e)
{
    double summ_e = 0.0;

    double last_element = -1.0; 
    int k = 2;
	
    while (fabs(last_element) >= e)
    {
        summ_e += last_element;
        last_element = get_next_element(last_element, k);
        ++k;
    }

    return summ_e;
}

int dinput(void)
{
    int number = 0;

    if (scanf_s("%d", &number) != 1 || !is_positive(number))
    {
		printf(stderr, "Your input is uncorrected");
		exit(1);
    }

    return number;
}

double finput(void)
{
    double number = 0.0;

    if (scanf_s("%lf", &number) != 1 || !is_positive_d(number))
    {
		printf(stderr, "Your input is uncorrected");
		exit(1);
    }

    return number;
}

bool is_positive(const int n)
{
    return n > 0;
}

bool is_positive_d(const double e)
{
    return e > DBL_EPSILON;
}

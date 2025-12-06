#include <stdio.h>
#include <math.h>
#include <float.h>
#include <locale.h>
#include <stdbool.h>


/*
* @brief Функция проверки ввода.
* @return Возвращает значение, если верное, иначе выдает ошибку.
*/
double Input(void);

/*
* @brief Проверяет корректность заданного интервала.
* @param start_x начальное значение интервала.
* @param finish_x конечное значение интервала.
* @return Возвращает ошибку если интервал задан неверно.
*/
void   CheckInterval(const double a, const double b);

/*
* @brief Проверяет корректность заданного шага.
* @param step_x значение шага.
* @return Возвращает ошибку если шаг задан неверно.
*/
void   CheckStep(const double dx);

/*
* @brief проверяет x > 0, т.к log(x) принимает значения только при x > 0
* @param x - конкретное значение x в данном шаге
*/
bool   CanCompute(const double x);     

/*
* @brief Считает нашу функцию.
* @param x - значение параметра.
* @return Значение функции.
*/
double Func(const double x);         
/*
* @brief Точка входа в программу.
* @return Возвращает значение функции с заданным в цикле корнем.
*/
int main(void)
{
    setlocale(LC_ALL, "Russian");
    printf("Введите начальный x: ");
    const double a = Input();
    printf("Введите конечный x: ");
    const double b = Input();
    printf("Введите шаг dx: ");
    const double dx = Input();
    CheckInterval(a, b);
    CheckStep(dx);
    printf("\nТаблица: y = sin(ln x) - cos(ln x) + 2 ln x\n");
    printf("%10s | %15s\n", "x", "y");
    printf("------------+-----------------\n");
    for (double x = a; x <= b + DBL_EPSILON; x += dx) {
        if (!CanCompute(x)) {
            printf("%10.3f | нет решения (x <= 0)\n", x);
        }
        else {
            printf("%10.3f | %15.6f\n", x, Func(x));
        }
    }
    return 0;
}

double Input(void)
{
    double num = 0;
    if (scanf_s("%lf", &num) != 1)
    {
        printf("Ошибка ввода!\n");
        exit(1);
    }
    return num;
}

void CheckInterval(const double a, const double b) {
    if (b - a < -DBL_EPSILON)
    { 
        printf("Конечное значение должно быть больше начального"); 
        exit(1); 
    }
}

void CheckStep(const double dx)
{
    if (dx <= DBL_EPSILON)
    {
        printf("Шаг должен быть не равен 0");
        exit(1);
    }
}

bool CanCompute(const double x)
{
    return x > DBL_EPSILON;
}

double Func(const double x)
{
    return sin(log(x)) - cos(log(x)) + 2 * log(x);
}

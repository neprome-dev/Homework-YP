#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
* @brief Функция input принимает вводимое значение
* @return Возвращает вводимое значение
*/
double input(void);

/**
* @brief Функция get_t считает значение изменения температуры
* @param Q отдаваемая энергия в джоулях
* @param m масса ложки в граммах
* @return Возвращает значение изменения температуры
*/
double get_t(const double Q, const double m);

/**
* @brief Функция is_number проверяет, больше ли число нуля
* @param number число для проверки
* @return Возвращает true, если число больше 0, если нет - false
*/
bool is_number(const double number);

/**
* @brief Точка входа в программу
* @return 0, если выполнена верно
*/
int main(void) {
	system("chcp 1251");

	puts("Введите значение Q (энергия в джоулях):");
	double Q = input();

	puts("Введите значение m (масса ложки в граммах):");
	double m = input();

	if (!is_number(m) || !is_number(Q)) {
		printf(stderr, "Параметры должны быть положительными");
		exit(1);
	}

	printf("Изменение температуры ΔT = %.4lf °C\n", get_t(Q, m));

	return 0;
}

double input(void) {
	double number = 0;
	if (scanf_s("%lf", &number) != 1) {
		printf(stderr, "Разрешен ввод только числа");
		exit(1);
	}

	return number;
}

double get_t(const double Q, const double m) {
	const double c = 462;
	return Q / (c * m);
}

bool is_number(const double number) {
	return number > 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MIN_RANGE -1000
#define MAX_RANGE 1000

/**
* @brief Считывает значение, введённое с клавиатуры, с проверкой ввода
* @return Считанное значение
*/
int getValid(void);

/**
* @brief Проверяет что переменная не меньше единицы
* @param input значение проверяемой переменной
*/
void checkValueForN(const int input);

/**
* @brief Проверяет, лежит ли число в указанном диапазоне
* @param input значение проверяемой переменной
* @param min минимальное значение
* @param max максимальное значение
*/
void checkValue(const int input, const int min, const int max);

/**
* @brief Находит сумму четных элементов
* @param arr массив
* @param size размер массива
* @return Сумма четных элементов
*/
int defForTask1(const int* arr, const size_t size);

/**
* @brief Подсчитывает количество двузначных элементов
* @param arr массив
* @param size размер массива
* @return Количество двузначных элементов
*/
int defForTask2(const int* arr, const size_t size);

/**
* @brief Заменяет последний отрицательный элемент на модуль первого
* @param arr массив
* @param size размер массива
*/
void defForTask3(int* arr, const size_t size);

/**
* @brief Находит индекс последнего отрицательного элемента
* @param arr массив
* @param size размер массива
* @return Индекс последнего отрицательного элемента
*/
int defFindLastNegativeIdx(const int* arr, const size_t size);

/**
* @brief Выбор способа заполнения
*/
enum { CHOICE_MANUAL = 1, CHOICE_RANDOM = 2 };

/**
* @brief Проверяет диапазон на корректность ввода
* @param min минимально возможный элемент
* @param max максимально возможный элемент
*/
void defCheckMinMax(const int min, const int max);

/**
* @brief Заполняет массив элементами, введёнными пользователем
* @param arr массив
* @param size размер массива
* @param min минимально возможный элемент
* @param max максимально возможный элемент
*/
void getManual(int* arr, const size_t size, const int min, const int max);

/**
* @brief Заполняет массив случайными элементами
* @param arr массив
* @param size размер массива
* @param min минимально возможный элемент
* @param max максимально возможный элемент
*/
void getRandom(int* arr, const size_t size, const int min, const int max);

/**
* @brief Выводит все элементы массива на экран
* @param arr массив
* @param size размер массива
*/
void defPrintArr(const int* arr, const size_t size);

/**
* @brief Проверяет корректно ли выделена память под массив
* @param arr массив
*/
void checkPointer(const int* arr);

/**
* @brief Точка входа в программу
* @return 0, если программа была выполнена корректно
*/
int main(void)
{
	system("chcp 1251");

	printf("Введите размер массива: ");
	int n = getValid();
	checkValueForN(n);

	int* arr = (int*)malloc(sizeof(int) * n);
	checkPointer(arr);

	printf("Введите диапазон, в котором будут задаваться числа массива:\n");
	printf("Минимум: ");
	const int min = getValid();
	printf("Максимум: ");
	const int max = getValid();
	defCheckMinMax(min, max);
	printf("Числа массива будут задаваться в диапазоне [%d, %d]\n\n", min, max);

	printf("Как будет заполнен массив?\n %d - Ручной ввод\n %d - Автоматический ввод\n", CHOICE_MANUAL, CHOICE_RANDOM);
	int choice = getValid();

	switch (choice)
	{
	case CHOICE_MANUAL:
		getManual(arr, (size_t)n, min, max);
		break;

	case CHOICE_RANDOM:
		getRandom(arr, (size_t)n, min, max);
		break;

	default:
		fprintf(stderr, "Ошибка\n");
		free(arr);
		exit(1);
	}

	defPrintArr(arr, (size_t)n);

	printf("\n--- Результаты обработки ---\n");
	printf("1. Сумма четных элементов = %d\n", defForTask1(arr, (size_t)n));
	printf("2. Количество двузначных элементов = %d\n", defForTask2(arr, (size_t)n));
	printf("3. Замена последнего отрицательного на модуль первого:\n");
	defForTask3(arr, (size_t)n);
	printf("\nНовый массив:\n");
	defPrintArr(arr, (size_t)n);

	free(arr);

	return 0;
}

int getValid(void)
{
	int valid = 0;
	if (!scanf_s("%d", &valid))
	{
		fprintf(stderr, "Ошибка\n");
		exit(1);
	}
	return valid;
}

void checkValueForN(const int input)
{
	if (input < 1)
	{
		fprintf(stderr, "Ошибка\nЧисло должно быть не меньше 1\n");
		exit(1);
	}
}

void checkValue(const int input, const int min, const int max)
{
	if (input > max || input < min)
	{
		fprintf(stderr, "Ошибка\nЧисло должно лежать в промежутке [%d;%d]\n", min, max);
		exit(1);
	}
}

void defCheckMinMax(const int min, const int max)
{
	if (min >= max)
	{
		fprintf(stderr, "Ошибка\nНеправильно указан диапазон\n");
		exit(1);
	}
}

void getManual(int* arr, const size_t size, const int min, const int max)
{
	checkPointer(arr);

	printf("\nВведите %zu элементов массива:\n", size);
	for (size_t i = 0; i < size; i++)
	{
		printf("A[%zu] = ", i);
		int num = getValid();
		checkValue(num, min, max);
		arr[i] = num;
	}
}

void getRandom(int* arr, const size_t size, const int min, const int max)
{
	checkPointer(arr);
	srand((unsigned int)time(NULL));

	for (size_t i = 0; i < size; i++)
	{
		int num = (rand() % (max - min + 1)) + min;
		arr[i] = num;
	}
}

void defPrintArr(const int* arr, const size_t size)
{
	checkPointer(arr);

	for (size_t i = 0; i < size; i++)
	{
		printf("A[%zu] = %d\n", i, arr[i]);
	}
}

int defForTask1(const int* arr, const size_t size)
{
	checkPointer(arr);

	int sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
		{
			sum += arr[i];
		}
	}
	return sum;
}

int defForTask2(const int* arr, const size_t size)
{
	checkPointer(arr);

	int count = 0;
	for (size_t i = 0; i < size; i++)
	{
		int absValue = arr[i] < 0 ? -arr[i] : arr[i];
		if (absValue >= 10 && absValue <= 99)
		{
			count++;
		}
	}
	return count;
}

int defFindLastNegativeIdx(const int* arr, const size_t size)
{
	checkPointer(arr);

	for (int i = (int)size - 1; i >= 0; i--)
	{
		if (arr[i] < 0)
		{
			return i;
		}
	}
	return -1;
}

void defForTask3(int* arr, const size_t size)
{
	checkPointer(arr);

	int lastNegativeIdx = defFindLastNegativeIdx(arr, size);

	if (lastNegativeIdx == -1)
	{
		printf("В массиве нет отрицательных элементов\n");
		return;
	}

	int firstElementAbs = arr[0] < 0 ? -arr[0] : arr[0];
	arr[lastNegativeIdx] = firstElementAbs;
}

void checkPointer(const int* arr)
{
	if (arr == NULL)
	{
		fprintf(stderr, "Ошибка выделения памяти\n");
		exit(1);
	}
}

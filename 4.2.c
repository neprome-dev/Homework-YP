#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

enum { CHOICE_MANUAL = 1, CHOICE_RANDOM = 2 };

/**
* @brief Считывает значение с клавиатуры с проверкой ввода
* @return Считанное значение
*/
int getValid(void);

/**
* @brief Проверяет, что число не меньше 1
* @param input проверяемое значение
*/
void checkValueForN(const int input);

/**
* @brief Проверяет, что число в диапазоне [min;max]
* @param input проверяемое значение
* @param min минимум
* @param max максимум
*/
void checkValue(const int input, const int min, const int max);

/**
* @brief Проверяет диапазон на корректность
* @param min минимум
* @param max максимум
*/
void defCheckMinMax(const int min, const int max);

/**
* @brief Заполняет массив вручную
* @param arr массив
* @param size размер
* @param min минимум
* @param max максимум
*/
void getManual(int* arr, const size_t size, const int min, const int max);

/**
* @brief Заполняет массив случайными числами
* @param arr массив
* @param size размер
* @param min минимум
* @param max максимум
*/
void getRandom(int* arr, const size_t size, const int min, const int max);

/**
* @brief Выводит массив на экран
* @param arr массив
* @param size размер
*/
void defPrintArr(const int* arr, const size_t size);

/**
* @brief Копирует массив
* @param arr массив
* @param size размер
* @return Новый массив
*/
int* defcopyArr(const int* arr, const size_t size);

/**
* @brief Проверяет указатель
* @param arr массив
*/
void checkPointer(const int* arr);

/**
* @brief Находит максимальный элемент
* @param arr массив
* @param size размер
* @return Максимум
*/
int defMAXX(const int* arr, const size_t size);

/**
* @brief Находит минимальный элемент
* @param arr массив
* @param size размер
* @return Минимум
*/
int defMINN(const int* arr, const size_t size);

/**
* @brief Заменяет первый отрицательный на первый положительный
* @param arr массив
* @param size размер
*/
void defForTask1(int* arr, const size_t size);

/**
* @brief Удаляет элементы кратные 7 из интервала [a;b]
* @param arr массив
* @param size размер
* @param a начало интервала
* @param b конец интервала
* @return Новый массив
*/
int* defForTask2(const int* arr, const size_t size, const int a, const int b);

/**
* @brief Формирует новый массив по формуле
* @param arr массив
* @param size размер
* @return Новый массив
*/
int* defForTask3(const int* arr, const size_t size);

/**
* @brief Считает новый размер массива после удаления
* @param arr массив
* @param size размер
* @param a начало интервала
* @param b конец интервала
* @return Новый размер
*/
size_t countAfterDelete(const int* arr, const size_t size, const int a, const int b);

/**
* @brief Точка входа в программу
* @return 0 если успех
*/
int main(void)
{
	system("chcp 1251");

	printf("Введите размер массива: ");
	int n = getValid();
	checkValueForN(n);

	int* D = (int*)malloc(sizeof(int) * n);
	checkPointer(D);

	printf("Введите диапазон:\n");
	printf("Минимум: ");
	int min = getValid();
	printf("Максимум: ");
	int max = getValid();
	defCheckMinMax(min, max);
	printf("Диапазон: [%d, %d]\n\n", min, max);

	printf("Как заполнить массив?\n %d - Ручной ввод\n %d - Случайные числа\n", CHOICE_MANUAL, CHOICE_RANDOM);
	int choice = getValid();

	switch (choice)
	{
	case CHOICE_MANUAL:
		getManual(D, (size_t)n, min, max);
		break;
	case CHOICE_RANDOM:
		getRandom(D, (size_t)n, min, max);
		break;
	default:
		fprintf(stderr, "Ошибка\n");
		free(D);
		return 1;
	}

	defPrintArr(D, (size_t)n);

	int* copyD = defcopyArr(D, (size_t)n);
	checkPointer(copyD);

	printf("\nКакие преобразования?\n%d - Заменить первый отрицательный на первый положительный\n%d - Удалить элементы кратные 7 из [a;b]\n%d - Сформировать массив A по формуле\n", 1, 2, 3);
	int taskChoice = getValid();

	switch (taskChoice)
	{
	case 1:
		defForTask1(copyD, (size_t)n);
		printf("\nМассив после замены:\n");
		defPrintArr(copyD, (size_t)n);
		break;

	case 2:
	{
		printf("Введите a: ");
		int a = getValid();
		printf("Введите b: ");
		int b = getValid();
		int* newArr = defForTask2(copyD, (size_t)n, a, b);
		size_t newSize = countAfterDelete(copyD, (size_t)n, a, b);
		printf("\nМассив после удаления:\n");
		defPrintArr(newArr, newSize);
		free(newArr);
		free(copyD);
		free(D);
		return 0;
	}

	case 3:
	{
		int* A = defForTask3(copyD, (size_t)n);
		printf("\nМассив A:\n");
		defPrintArr(A, (size_t)n);
		free(A);
		free(copyD);
		free(D);
		return 0;
	}

	default:
		fprintf(stderr, "Разрешен ввод только чисел\n");
		free(D);
		free(copyD);
		return 1;

		free(D);
		free(copyD);
		return 0;
	}
}

int getValid(void)
{
	int valid = 0;
	if (!scanf_s("%d", &valid))
	{
		fprintf(stderr, "Разрешен ввод только чисел\n");
		exit(1);
	}
	return valid;
}

void checkValueForN(const int input)
{
	if (input < 1)
	{
		fprintf(stderr, "Размер должен быть больше или равен 1\n");
		exit(1);
	}
}

void checkValue(const int input, const int min, const int max)
{
	if (input < min || input > max)
	{
		fprintf(stderr, "Не в диапазоне [%d;%d]\n", min, max);
		exit(1);
	}
}

void defCheckMinMax(const int min, const int max)
{
	if (min >= max)
	{
		fprintf(stderr, "Ошибка: мин должен быть < макс\n");
		exit(1);
	}
}

void getManual(int* arr, const size_t size, const int min, const int max)
{
	checkPointer(arr);
	printf("\nВведите %zu элементов:\n", size);
	for (size_t i = 0; i < size; i++)
	{
		printf("D[%zu] = ", i);
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
		arr[i] = (rand() % (max - min + 1)) + min;
	}
}

void defPrintArr(const int* arr, const size_t size)
{
	checkPointer(arr);
	for (size_t i = 0; i < size; i++)
	{
		printf("D[%zu] = %d\n", i, arr[i]);
	}
}

int* defcopyArr(const int* arr, const size_t size)
{
	checkPointer(arr);
	int* copy = (int*)malloc(sizeof(int) * size);
	checkPointer(copy);
	for (size_t i = 0; i < size; i++)
	{
		copy[i] = arr[i];
	}
	return copy;
}

void checkPointer(const int* arr)
{
	if (arr == NULL)
	{
		fprintf(stderr, "Ошибка памяти\n");
		exit(1);
	}
}

int defMAXX(const int* arr, const size_t size)
{
	checkPointer(arr);
	int max = arr[0];
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

int defMINN(const int* arr, const size_t size)
{
	checkPointer(arr);
	int min = arr[0];
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}

void defForTask1(int* arr, const size_t size)
{
	checkPointer(arr);

	int negIdx = -1, posIdx = -1;

	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] < 0 && negIdx == -1)
			negIdx = (int)i;
		if (arr[i] > 0 && posIdx == -1)
			posIdx = (int)i;
	}

	if (negIdx != -1 && posIdx != -1)
	{
		int temp = arr[negIdx];
		arr[negIdx] = arr[posIdx];
		arr[posIdx] = temp;
	}
}

size_t countAfterDelete(const int* arr, const size_t size, const int a, const int b)
{
	checkPointer(arr);
	size_t count = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (!(arr[i] % 7 == 0 && arr[i] >= a && arr[i] <= b))
			count++;
	}

	return count;
}

int* defForTask2(const int* arr, const size_t size, const int a, const int b)
{
	checkPointer(arr);

	size_t newSize = countAfterDelete(arr, size, a, b);
	int* newArr = (int*)malloc(sizeof(int) * newSize);
	checkPointer(newArr);

	size_t j = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (!(arr[i] % 7 == 0 && arr[i] >= a && arr[i] <= b))
		{
			newArr[j++] = arr[i];
		}
	}

	return newArr;
}

int* defForTask3(const int* arr, const size_t size)
{
	checkPointer(arr);

	int* A = (int*)malloc(sizeof(int) * size);
	checkPointer(A);

	for (size_t i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			A[i] = arr[i] * arr[i] + (int)i;
		}
		else
		{
			A[i] = (int)i * arr[i];
		}
	}

	return A;
}

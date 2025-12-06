#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { MANUAL = 1, RANDOM = 2, TASK_ONE = 1, TASK_TWO = 2 };

/**
* @brief Считывает значение с проверкой
* @return Число
*/
int getValid(void);

/**
* @brief Проверяет размер > 0
* @param input размер
*/
void checkSize(const int input);

/**
* @brief Проверяет диапазон
* @param min минимум
* @param max максимум
*/
void checkMinMax(const int min, const int max);

/**
* @brief Проверяет число в диапазоне
* @param value число
* @param min минимум
* @param max максимум
*/
void checkValue(const int value, const int min, const int max);

/**
* @brief Выделяет память под 2D массив
* @param n строк
* @param m столбцов
* @return 2D массив
*/
int** getMakeArrays(const size_t n, const size_t m);

/**
* @brief Проверяет память
* @param arr массив
* @param n строк
*/
void checkMemory(int** arr, const size_t n);

/**
* @brief Копирует массив
* @param arr исходный массив
* @param n строк
* @param m столбцов
* @return Копия массива
*/
int** getCopyArray(int** arr, const size_t n, const size_t m);

/**
* @brief Заполняет массив вручную
* @param arr массив
* @param n строк
* @param m столбцов
* @param min минимум
* @param max максимум
*/
void getManual(int** arr, const size_t n, const size_t m, const int min, const int max);

/**
* @brief Заполняет массив случайно
* @param arr массив
* @param n строк
* @param m столбцов
* @param min минимум
* @param max максимум
*/
void getRandom(int** arr, const size_t n, const size_t m, const int min, const int max);

/**
* @brief Выводит массив
* @param arr массив
* @param n строк
* @param m столбцов
*/
void printArrays(int** arr, const size_t n, const size_t m);

/**
* @brief Освобождает память
* @param arr массив
* @param n строк
*/
void freeMemory(int** arr, const size_t n);

/**
* @brief Задание 1: заменить минимальный по модулю элемент в каждом столбце на противоположный
* @param arr массив
* @param n строк
* @param m столбцов
*/
void defTaskOne(int** arr, const size_t n, const size_t m);

/**
* @brief Найти максимальный элемент во всем массиве
* @param arr массив
* @param n строк
* @param m столбцов
* @return Максимум
*/
int findMaxElement(int** arr, const size_t n, const size_t m);

/**
* @brief Задание 2: удалить все строки, содержащие максимальные элементы
* @param arr массив
* @param n строк
* @param m столбцов
* @return Новый размер массива (количество строк)
*/
size_t defTaskTwo(int** arr, const size_t n, const size_t m);

/**
* @brief Точка входа в программу
* @return 0
*/
int main(void)
{
	system("chcp 1251");

	printf("Введите количество строк: ");
	int n_input = getValid();
	checkSize(n_input);
	size_t n = (size_t)n_input;

	printf("Введите количество столбцов: ");
	int m_input = getValid();
	checkSize(m_input);
	size_t m = (size_t)m_input;

	printf("Введите минимум: ");
	int min = getValid();
	printf("Введите максимум: ");
	int max = getValid();
	checkMinMax(min, max);

	int** mainArray = getMakeArrays(n, m);
	checkMemory(mainArray, n);

	printf("\nВыберите способ заполнения:\n%d - Ручной\n%d - Случайный\n", MANUAL, RANDOM);
	int choice = getValid();

	switch (choice)
	{
	case MANUAL:
		getManual(mainArray, n, m, min, max);
		break;
	case RANDOM:
		getRandom(mainArray, n, m, min, max);
		break;
	default:
		fprintf(stderr, "Ошибка\n");
		freeMemory(mainArray, n);
		exit(1);
	}

	int** copyArray = getCopyArray(mainArray, n, m);
	checkMemory(copyArray, n);

	printf("\nИсходный массив:\n");
	printArrays(copyArray, n, m);

	printf("\nВыберите задание:\n%d - Заменить минимальный по модулю в каждом столбце\n%d - Удалить строки с максимальными элементами\n", TASK_ONE, TASK_TWO);
	int taskChoice = getValid();

	switch (taskChoice)
	{
	case TASK_ONE:
		defTaskOne(copyArray, n, m);
		printf("\nМассив после замены:\n");
		printArrays(copyArray, n, m);
		break;

	case TASK_TWO:
	{
		size_t newN = defTaskTwo(copyArray, n, m);
		printf("\nМассив после удаления:\n");
		printArrays(copyArray, newN, m);
		printf("\nУдалено %zu строк\n", n - newN);
		break;
	}

	default:
		fprintf(stderr, "Ошибка\n");
		freeMemory(mainArray, n);
		freeMemory(copyArray, n);
		exit(1);
	}

	freeMemory(mainArray, n);
	freeMemory(copyArray, n);

	return 0;
}

int getValid(void)
{
	int valid = 0;
	if (!scanf_s("%d", &valid))
	{
		fprintf(stderr, "Ошибка ввода\n");
		exit(1);
	}
	return valid;
}

void checkSize(const int input)
{
	if (input < 1)
	{
		fprintf(stderr, "Размер >= 1\n");
		exit(1);
	}
}

void checkMinMax(const int min, const int max)
{
	if (min >= max)
	{
		fprintf(stderr, "min < max\n");
		exit(1);
	}
}

void checkValue(const int value, const int min, const int max)
{
	if (value < min || value > max)
	{
		fprintf(stderr, "Значение должно быть в [%d;%d]\n", min, max);
		exit(1);
	}
}

int** getMakeArrays(const size_t n, const size_t m)
{
	int** arr = (int**)malloc(sizeof(int*) * n);

	if (arr == NULL)
	{
		fprintf(stderr, "Ошибка памяти\n");
		exit(1);
	}

	for (size_t i = 0; i < n; i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * m);
		if (arr[i] == NULL)
		{
			fprintf(stderr, "Ошибка памяти\n");
			exit(1);
		}
	}
	return arr;
}

void checkMemory(int** arr, const size_t n)
{
	if (arr == NULL)
	{
		fprintf(stderr, "Ошибка памяти\n");
		exit(1);
	}
	for (size_t i = 0; i < n; i++)
	{
		if (arr[i] == NULL)
		{
			fprintf(stderr, "Ошибка памяти\n");
			exit(1);
		}
	}
}

int** getCopyArray(int** arr, const size_t n, const size_t m)
{
	checkMemory(arr, n);
	int** copy = getMakeArrays(n, m);
	checkMemory(copy, n);

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			copy[i][j] = arr[i][j];
		}
	}
	return copy;
}

void getManual(int** arr, const size_t n, const size_t m, const int min, const int max)
{
	checkMemory(arr, n);
	printf("\nВведите %zu элементов:\n", n * m);

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			printf("A[%zu][%zu] = ", i, j);
			int num = getValid();
			checkValue(num, min, max);
			arr[i][j] = num;
		}
	}
}

void getRandom(int** arr, const size_t n, const size_t m, const int min, const int max)
{
	checkMemory(arr, n);
	srand((unsigned int)time(NULL));

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			arr[i][j] = (rand() % (max - min + 1)) + min;
		}
	}
}

void printArrays(int** arr, const size_t n, const size_t m)
{
	checkMemory(arr, n);

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			printf("%7d", arr[i][j]);
		}
		printf("\n");
	}
}

void freeMemory(int** arr, const size_t n)
{
	if (arr != NULL)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (arr[i] != NULL)
				free(arr[i]);
		}
		free(arr);
	}
}

void defTaskOne(int** arr, const size_t n, const size_t m)
{
	checkMemory(arr, n);

	for (size_t j = 0; j < m; j++)
	{
		int minAbs = abs(arr[0][j]);
		size_t minIdx = 0;

		for (size_t i = 0; i < n; i++)
		{
			if (abs(arr[i][j]) < minAbs)
			{
				minAbs = abs(arr[i][j]);
				minIdx = i;
			}
		}

		arr[minIdx][j] = -arr[minIdx][j];
	}
}

int findMaxElement(int** arr, const size_t n, const size_t m)
{
	checkMemory(arr, n);

	int max = arr[0][0];
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (arr[i][j] > max)
				max = arr[i][j];
		}
	}
	return max;
}

size_t defTaskTwo(int** arr, const size_t n, const size_t m)
{
	checkMemory(arr, n);

	int maxVal = findMaxElement(arr, n, m);
	size_t newN = 0;

	for (size_t i = 0; i < n; i++)
	{
		int hasMax = 0;
		for (size_t j = 0; j < m; j++)
		{
			if (arr[i][j] == maxVal)
			{
				hasMax = 1;
				break;
			}
		}

		if (!hasMax)
		{
			for (size_t j = 0; j < m; j++)
			{
				arr[newN][j] = arr[i][j];
			}
			newN++;
		}
	}

	return newN;
}

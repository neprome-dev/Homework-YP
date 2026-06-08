#include <iostream>
#include "../include/ClassPriorityDeque.h"

using namespace std;

/**
* @brief Точка входа в программу
* @return Если программа выполнена корректно - 0, иначе 1
*/
int main()
{
	cout << "Вариант 10\n";
	cout << "Очередь с приоритетом с двусторонним доступом\n\n";

	PriorityDeque queue = { 5, 1, 9, 3, 7 };

	cout << "Исходная очередь: " << queue.toString() << '\n';
	cout << "Минимальный приоритет: " << queue.getMin() << '\n';
	cout << "Максимальный приоритет: " << queue.getMax() << "\n\n";

	queue.insert(4);
	queue << 10;

	cout << "Очередь после добавления элементов: " << queue.toString() << '\n';

	cout << "Удалён элемент с наименьшим приоритетом: " << queue.removeMin() << '\n';

	int value = 0;
	queue >> value;

	cout << "Удалён элемент с наибольшим приоритетом: " << value << '\n';
	cout << "Очередь после удаления элементов: " << queue.toString() << '\n';

	return 0;
}

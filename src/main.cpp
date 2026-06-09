#include <iostream>
#include "../include/ClassPriorityDeque.h"

using namespace std;

/**
* @brief Точка входа в программу
* @return Код завершения программы
*/
int main()
{
	cout << "Вариант 10\n";
	cout << "Очередь с приоритетом с двусторонним доступом\n\n";

	// Элементы задаются парами {значение, приоритет}
	PriorityDeque queue = { {100, 5}, {200, 1}, {300, 9}, {400, 3} };

	cout << "Очередь {значение(приоритет)}: " << queue.toString() << "\n\n";

	cout << "Элемент с наименьшим приоритетом: значение " << queue.getMin()
		<< ", приоритет " << queue.getMinPriority() << '\n';
	cout << "Элемент с наибольшим приоритетом: значение " << queue.getMax()
		<< ", приоритет " << queue.getMaxPriority() << "\n\n";

	// Добавление элемента двумя способами
	queue.insert(500, 7);
	queue << make_pair(600, 2);

	cout << "После добавления элементов: " << queue.toString() << "\n\n";

	cout << "Удалён элемент с наименьшим приоритетом, его значение: " << queue.removeMin() << '\n';

	int value = 0;
	queue >> value;
	cout << "Удалён элемент с наибольшим приоритетом, его значение: " << value << '\n';

	cout << "\nИтоговая очередь: " << queue.toString() << '\n';
	cout << "Пуста ли очередь? " << (queue.isEmpty() ? "да" : "нет") << '\n';

	return 0;
}

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

	PriorityDeque queue;

	queue.insert("Помыть посуду", 5);
	queue.insert("Вызвать скорую", 1);
	queue.insert("Сделать домашку", 9);
	queue.insert("Купить хлеб", 3);

	cout << "Очередь задач: " << queue.toString() << "\n\n";

	cout << "Самый срочный (минимальный приоритет): "
		<< queue.getMin() << " [приоритет " << queue.getMinPriority() << "]\n";
	cout << "Наименее срочный (максимальный приоритет): "
		<< queue.getMax() << " [приоритет " << queue.getMaxPriority() << "]\n\n";

	cout << "Выполнили самую срочную задачу: " << queue.removeMin() << '\n';
	cout << "Отложили наименее срочную задачу: " << queue.removeMax() << '\n';

	cout << "\nОставшиеся задачи: " << queue.toString() << '\n';

	return 0;
}

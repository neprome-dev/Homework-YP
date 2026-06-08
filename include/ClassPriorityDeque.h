#pragma once
#include <vector>
#include <string>
#include <initializer_list>

using namespace std;

/**
* @brief Класс "Очередь с приоритетом с двусторонним доступом"
*/
class PriorityDeque
{
private:
	/**
	* @param data - коллекция элементов очереди
	*/
	vector<int> data;

	/**
	* @brief Проверяет очередь на пустоту
	*/
	void checkEmpty(void) const;

public:
	/**
	* @brief Базовый конструктор по-умолчанию, создаёт пустую очередь
	*/
	PriorityDeque(void) = default;

	/**
	* @brief Конструктор, принимающий список инициализации целых чисел
	* @param values - список значений, добавляемых в очередь
	*/
	PriorityDeque(const initializer_list<int> values);

	/**
	* @brief Конструктор копирования по-умолчанию
	*/
	PriorityDeque(const PriorityDeque& other) = default;

	/**
	* @brief Конструктор перемещения по-умолчанию
	*/
	PriorityDeque(PriorityDeque&& other) noexcept = default;

	/**
	* @brief Оператор приравнивания, присваивает значения другой очереди
	* @param other - очередь, на чьи значения будет происходить замена
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator = (const PriorityDeque& other) = default;

	/**
	* @brief Оператор перемещающего приравнивания
	* @param other - очередь, значения которой будут перемещены
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator = (PriorityDeque&& other) noexcept = default;

	/**
	* @brief Деструктор по-умолчанию
	*/
	~PriorityDeque(void) = default;

	/**
	* @brief Добавляет элемент в очередь с приоритетом
	* @param value - добавляемое значение
	*/
	void insert(const int value);

	/**
	* @brief Удаляет элемент с наименьшим приоритетом
	* @return Удалённое значение
	*/
	int removeMin(void);

	/**
	* @brief Удаляет элемент с наибольшим приоритетом
	* @return Удалённое значение
	*/
	int removeMax(void);

	/**
	* @brief Получает элемент с наименьшим приоритетом
	* @return Значение с наименьшим приоритетом
	*/
	int getMin(void) const;

	/**
	* @brief Получает элемент с наибольшим приоритетом
	* @return Значение с наибольшим приоритетом
	*/
	int getMax(void) const;

	/**
	* @brief Получает количество элементов очереди
	* @return Количество элементов
	*/
	size_t getSize(void) const;

	/**
	* @brief Проверяет очередь на пустоту
	* @return Если очередь пустая - 1, иначе 0
	*/
	bool isEmpty(void) const;

	/**
	* @brief Получает строковое представление очереди
	* @return Очередь в формате [a, b, c]
	*/
	string toString(void) const;

	/**
	* @brief Оператор сдвига влево, добавляет элемент в очередь
	* @param value - добавляемое значение
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator << (const int value);

	/**
	* @brief Оператор сдвига вправо, извлекает элемент с наибольшим приоритетом
	* @param value - переменная, в которую будет записан извлечённый элемент
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator >> (int& value);
};

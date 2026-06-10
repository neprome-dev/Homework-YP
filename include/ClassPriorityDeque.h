#pragma once
#include <string>
#include <initializer_list>
#include <utility>

/**
* @brief Элемент очереди с приоритетом
*
* Хранит целочисленные данные и их целочисленный приоритет раздельно.
*/
struct Node
{
	/**
	* @param value - целочисленные данные элемента
	*/
	int value;

	/**
	* @param priority - приоритет элемента, по которому происходит упорядочивание
	*/
	int priority;
};

/**
* @brief Класс "Очередь с приоритетом с двусторонним доступом"
*
* Коллекция целых чисел. Каждому элементу сопоставлен приоритет.
* Элементы хранятся в массиве, упорядоченном по возрастанию приоритета:
* элемент с наименьшим приоритетом находится в начале, с наибольшим - в конце.
*/
class PriorityDeque
{
private:
	/**
	* @param data - массив элементов очереди (упорядочен по приоритету)
	*/
	Node* data;

	/**
	* @param count - количество элементов очереди
	*/
	size_t count;

public:
	/**
	* @brief Конструктор по-умолчанию, создаёт пустую очередь
	*/
	PriorityDeque(void);

	/**
	* @brief Конструктор со списком инициализации
	*
	* Каждая пара значений списка задаёт элемент в формате {значение, приоритет}.
	* @param values - список пар {значение, приоритет}
	*/
	PriorityDeque(const std::initializer_list<std::pair<int, int>>& values);

	/**
	* @brief Конструктор копирования
	* @param other - очередь, которая будет скопирована
	*/
	PriorityDeque(const PriorityDeque& other);

	/**
	* @brief Конструктор перемещения
	* @param other - очередь, ресурсы которой будут перемещены
	*/
	PriorityDeque(PriorityDeque&& other) noexcept;

	/**
	* @brief Оператор присваивания
	* @param other - очередь, значения которой будут скопированы
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator = (const PriorityDeque& other);

	/**
	* @brief Оператор перемещающего присваивания
	* @param other - очередь, ресурсы которой будут перемещены
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator = (PriorityDeque&& other) noexcept;

	/**
	* @brief Деструктор, освобождает выделенную память
	*/
	~PriorityDeque(void);

	/**
	* @brief Добавляет элемент в очередь с сохранением порядка по приоритету
	* @param value - целочисленные данные элемента
	* @param priority - приоритет элемента
	*/
	void insert(const int value, const int priority);

	/**
	* @brief Удаляет элемент с наименьшим приоритетом
	* @return Данные удалённого элемента
	*/
	int removeMin(void);

	/**
	* @brief Удаляет элемент с наибольшим приоритетом
	* @return Данные удалённого элемента
	*/
	int removeMax(void);

	/**
	* @brief Возвращает данные элемента с наименьшим приоритетом (поиск)
	* @return Данные элемента с наименьшим приоритетом
	*/
	int getMin(void) const;

	/**
	* @brief Возвращает данные элемента с наибольшим приоритетом (поиск)
	* @return Данные элемента с наибольшим приоритетом
	*/
	int getMax(void) const;

	/**
	* @brief Возвращает наименьший приоритет в очереди
	* @return Наименьший приоритет
	*/
	int getMinPriority(void) const;

	/**
	* @brief Возвращает наибольший приоритет в очереди
	* @return Наибольший приоритет
	*/
	int getMaxPriority(void) const;

	/**
	* @brief Возвращает количество элементов очереди
	* @return Количество элементов
	*/
	size_t getSize(void) const;

	/**
	* @brief Проверяет, пуста ли очередь
	* @return true, если очередь пуста, иначе false
	*/
	bool isEmpty(void) const;

	/**
	* @brief Возвращает строковое представление очереди
	* @return Очередь в формате [значение(приоритет), значение(приоритет)]
	*/
	std::string toString(void) const;

	/**
	* @brief Оператор сдвига влево: добавляет элемент в очередь
	* @param element - пара {значение, приоритет}
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator << (const std::pair<int, int>& element);

	/**
	* @brief Оператор сдвига вправо: извлекает элемент с наибольшим приоритетом
	* @param value - переменная, в которую записываются данные извлечённого элемента
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator >> (int& value);
};

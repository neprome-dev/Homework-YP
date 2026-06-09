#pragma once
#include <string>

/**
* @brief Элемент очереди: хранит данные и их приоритет раздельно
*/
struct Node
{
	/**
	* @param value - полезные данные элемента
	*/
	std::string value;

	/**
	* @param priority - приоритет элемента, по которому происходит упорядочивание
	*/
	int priority;
};

/**
* @brief Класс "Очередь с приоритетом с двусторонним доступом"
*
* Элементы хранятся в массиве, упорядоченном по возрастанию приоритета.
* Элемент с наименьшим приоритетом находится в начале, с наибольшим - в конце.
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

	/**
	* @brief Выводит сообщение об ошибке и завершает работу программы
	* @param text - текст, выводимый на экран
	*/
	void ERROR(const std::string text) const;

public:
	/**
	* @brief Базовый конструктор по-умолчанию, создаёт пустую очередь
	*/
	PriorityDeque(void);

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
	* @param value - данные добавляемого элемента
	* @param priority - приоритет добавляемого элемента
	*/
	void insert(const std::string& value, int priority);

	/**
	* @brief Удаляет элемент с наименьшим приоритетом
	* @return Данные удалённого элемента
	*/
	std::string removeMin(void);

	/**
	* @brief Удаляет элемент с наибольшим приоритетом
	* @return Данные удалённого элемента
	*/
	std::string removeMax(void);

	/**
	* @brief Получает данные элемента с наименьшим приоритетом
	* @return Данные элемента с наименьшим приоритетом
	*/
	std::string getMin(void) const;

	/**
	* @brief Получает данные элемента с наибольшим приоритетом
	* @return Данные элемента с наибольшим приоритетом
	*/
	std::string getMax(void) const;

	/**
	* @brief Получает приоритет элемента с наименьшим приоритетом
	* @return Наименьший приоритет в очереди
	*/
	int getMinPriority(void) const;

	/**
	* @brief Получает приоритет элемента с наибольшим приоритетом
	* @return Наибольший приоритет в очереди
	*/
	int getMaxPriority(void) const;

	/**
	* @brief Получает количество элементов очереди
	* @return Количество элементов
	*/
	size_t getSize(void) const;

	/**
	* @brief Проверяет очередь на пустоту
	* @return Если очередь пустая - true, иначе false
	*/
	bool isEmpty(void) const;

	/**
	* @brief Получает строковое представление очереди
	* @return Очередь в формате [value(priority), value(priority)]
	*/
	std::string toString(void) const;
};

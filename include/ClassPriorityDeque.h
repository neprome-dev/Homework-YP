#pragma once
#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

/**
* @brief Класс "Очередь с приоритетом с двусторонним доступом"
* @tparam Type - тип хранимых элементов
*/
template<typename Type>
class PriorityDeque
{
private:
	/**
	* @param data - массив элементов очереди (хранится по возрастанию)
	*/
	Type* data;

	/**
	* @param count - количество элементов очереди
	*/
	size_t count;

	/**
	* @brief Выводит ошибку и завершает работу программы
	* @param text - текст, выводимый на экран
	*/
	void ERROR(const string text) const
	{
		cerr << text;
		exit(1);
	}

public:
	/**
	* @brief Базовый конструктор по-умолчанию, создаёт пустую очередь
	*/
	PriorityDeque(void) : data(nullptr), count(0) {}

	/**
	* @brief Конструктор, принимающий список инициализации
	* @param values - список значений, добавляемых в очередь
	*/
	PriorityDeque(const initializer_list<Type> values) : data(nullptr), count(0)
	{
		for (const Type& value : values)
		{
			insert(value);
		}
	}

	/**
	* @brief Конструктор копирования
	* @param other - очередь, которая будет скопирована
	*/
	PriorityDeque(const PriorityDeque& other) : data(nullptr), count(other.count)
	{
		if (count > 0)
		{
			data = new Type[count];
			for (size_t i = 0; i < count; i++)
			{
				data[i] = other.data[i];
			}
		}
	}

	/**
	* @brief Конструктор перемещения
	* @param other - очередь, ресурсы которой будут перемещены
	*/
	PriorityDeque(PriorityDeque&& other) noexcept : data(other.data), count(other.count)
	{
		other.data = nullptr;
		other.count = 0;
	}

	/**
	* @brief Оператор присваивания
	* @param other - очередь, значения которой будут скопированы
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator = (const PriorityDeque& other)
	{
		if (this != &other)
		{
			delete[] data;

			count = other.count;
			data = (count > 0) ? new Type[count] : nullptr;
			for (size_t i = 0; i < count; i++)
			{
				data[i] = other.data[i];
			}
		}

		return *this;
	}

	/**
	* @brief Оператор перемещающего присваивания
	* @param other - очередь, ресурсы которой будут перемещены
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator = (PriorityDeque&& other) noexcept
	{
		if (this != &other)
		{
			delete[] data;

			data = other.data;
			count = other.count;

			other.data = nullptr;
			other.count = 0;
		}

		return *this;
	}

	/**
	* @brief Деструктор, освобождает выделенную память
	*/
	~PriorityDeque(void)
	{
		delete[] data;
	}

	/**
	* @brief Добавляет элемент в очередь с сохранением порядка по возрастанию
	* @param value - добавляемое значение
	*/
	void insert(const Type& value)
	{
		size_t index = 0;

		while (index < count && data[index] <= value)
		{
			++index;
		}

		Type* newdata = new Type[count + 1];

		for (size_t i = 0; i < index; i++)
		{
			newdata[i] = data[i];
		}

		newdata[index] = value;

		for (size_t i = index; i < count; i++)
		{
			newdata[i + 1] = data[i];
		}

		delete[] data;
		data = newdata;
		++count;
	}

	/**
	* @brief Удаляет элемент с наименьшим приоритетом
	* @return Удалённое значение
	*/
	Type removeMin(void)
	{
		if (isEmpty())
		{
			ERROR("Очередь пуста");
		}

		const Type value = data[0];

		Type* newdata = (count - 1 > 0) ? new Type[count - 1] : nullptr;
		for (size_t i = 1; i < count; i++)
		{
			newdata[i - 1] = data[i];
		}

		delete[] data;
		data = newdata;
		--count;

		return value;
	}

	/**
	* @brief Удаляет элемент с наибольшим приоритетом
	* @return Удалённое значение
	*/
	Type removeMax(void)
	{
		if (isEmpty())
		{
			ERROR("Очередь пуста");
		}

		const Type value = data[count - 1];

		Type* newdata = (count - 1 > 0) ? new Type[count - 1] : nullptr;
		for (size_t i = 0; i + 1 < count; i++)
		{
			newdata[i] = data[i];
		}

		delete[] data;
		data = newdata;
		--count;

		return value;
	}

	/**
	* @brief Получает элемент с наименьшим приоритетом
	* @return Значение с наименьшим приоритетом
	*/
	Type getMin(void) const
	{
		if (isEmpty())
		{
			ERROR("Очередь пуста");
		}

		return data[0];
	}

	/**
	* @brief Получает элемент с наибольшим приоритетом
	* @return Значение с наибольшим приоритетом
	*/
	Type getMax(void) const
	{
		if (isEmpty())
		{
			ERROR("Очередь пуста");
		}

		return data[count - 1];
	}

	/**
	* @brief Получает количество элементов очереди
	* @return Количество элементов
	*/
	size_t getSize(void) const
	{
		return count;
	}

	/**
	* @brief Проверяет очередь на пустоту
	* @return Если очередь пустая - true, иначе false
	*/
	bool isEmpty(void) const
	{
		return count == 0;
	}

	/**
	* @brief Получает строковое представление очереди
	* @return Очередь в формате [a, b, c]
	*/
	string toString(void) const
	{
		string result = "[";

		for (size_t i = 0; i < count; ++i)
		{
			result += to_string(data[i]);

			if (i + 1 < count)
			{
				result += ", ";
			}
		}

		result += "]";

		return result;
	}

	/**
	* @brief Оператор сдвига влево, добавляет элемент в очередь
	* @param value - добавляемое значение
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator << (const Type& value)
	{
		insert(value);

		return *this;
	}

	/**
	* @brief Оператор сдвига вправо, извлекает элемент с наибольшим приоритетом
	* @param value - переменная, в которую будет записан извлечённый элемент
	* @return Ссылка на текущую очередь
	*/
	PriorityDeque& operator >> (Type& value)
	{
		value = removeMax();

		return *this;
	}
};

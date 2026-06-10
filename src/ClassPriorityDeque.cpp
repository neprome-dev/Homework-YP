#include "../include/ClassPriorityDeque.h"
#include <stdexcept>

using namespace std;

PriorityDeque::PriorityDeque(void) : data(nullptr), count(0) {}

PriorityDeque::PriorityDeque(const initializer_list<pair<int, int>>& values) : data(nullptr), count(0)
{
	for (const pair<int, int>& element : values)
	{
		insert(element.first, element.second);
	}
}

PriorityDeque::PriorityDeque(const PriorityDeque& other) : data(nullptr), count(other.count)
{
	if (count > 0)
	{
		data = new Node[count];
		for (size_t i = 0; i < count; i++)
		{
			data[i] = other.data[i];
		}
	}
}

PriorityDeque::PriorityDeque(PriorityDeque&& other) noexcept : data(other.data), count(other.count)
{
	other.data = nullptr;
	other.count = 0;
}

PriorityDeque& PriorityDeque::operator = (const PriorityDeque& other)
{
	if (this != &other)
	{
		delete[] data;

		count = other.count;
		data = (count > 0) ? new Node[count] : nullptr;
		for (size_t i = 0; i < count; i++)
		{
			data[i] = other.data[i];
		}
	}

	return *this;
}

PriorityDeque& PriorityDeque::operator = (PriorityDeque&& other) noexcept
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

PriorityDeque::~PriorityDeque(void)
{
	delete[] data;
}

void PriorityDeque::insert(const int value, const int priority)
{
	size_t index = 0;

	while (index < count && data[index].priority <= priority)
	{
		++index;
	}

	Node* newdata = new Node[count + 1];

	for (size_t i = 0; i < index; i++)
	{
		newdata[i] = data[i];
	}

	newdata[index].value = value;
	newdata[index].priority = priority;

	for (size_t i = index; i < count; i++)
	{
		newdata[i + 1] = data[i];
	}

	delete[] data;
	data = newdata;
	++count;
}

int PriorityDeque::removeMin(void)
{
	if (isEmpty())
	{
		throw out_of_range("ÐÑÐµÑÐµÐ´Ñ Ð¿ÑÑÑÐ°");
	}

	const int value = data[0].value;

	Node* newdata = (count - 1 > 0) ? new Node[count - 1] : nullptr;
	for (size_t i = 1; i < count; i++)
	{
		newdata[i - 1] = data[i];
	}

	delete[] data;
	data = newdata;
	--count;

	return value;
}

int PriorityDeque::removeMax(void)
{
	if (isEmpty())
	{
		throw out_of_range("ÐÑÐµÑÐµÐ´Ñ Ð¿ÑÑÑÐ°");
	}

	const int value = data[count - 1].value;

	Node* newdata = (count - 1 > 0) ? new Node[count - 1] : nullptr;
	for (size_t i = 0; i + 1 < count; i++)
	{
		newdata[i] = data[i];
	}

	delete[] data;
	data = newdata;
	--count;

	return value;
}

int PriorityDeque::getMin(void) const
{
	if (isEmpty())
	{
		throw out_of_range("ÐÑÐµÑÐµÐ´Ñ Ð¿ÑÑÑÐ°");
	}

	return data[0].value;
}

int PriorityDeque::getMax(void) const
{
	if (isEmpty())
	{
		throw out_of_range("ÐÑÐµÑÐµÐ´Ñ Ð¿ÑÑÑÐ°");
	}

	return data[count - 1].value;
}

int PriorityDeque::getMinPriority(void) const
{
	if (isEmpty())
	{
		throw out_of_range("ÐÑÐµÑÐµÐ´Ñ Ð¿ÑÑÑÐ°");
	}

	return data[0].priority;
}

int PriorityDeque::getMaxPriority(void) const
{
	if (isEmpty())
	{
		throw out_of_range("ÐÑÐµÑÐµÐ´Ñ Ð¿ÑÑÑÐ°");
	}

	return data[count - 1].priority;
}

size_t PriorityDeque::getSize(void) const
{
	return count;
}

bool PriorityDeque::isEmpty(void) const
{
	return count == 0;
}

string PriorityDeque::toString(void) const
{
	string result = "[";

	for (size_t i = 0; i < count; ++i)
	{
		result += to_string(data[i].value) + "(" + to_string(data[i].priority) + ")";

		if (i + 1 < count)
		{
			result += ", ";
		}
	}

	result += "]";

	return result;
}

PriorityDeque& PriorityDeque::operator << (const pair<int, int>& element)
{
	insert(element.first, element.second);

	return *this;
}

PriorityDeque& PriorityDeque::operator >> (int& value)
{
	value = removeMax();

	return *this;
}

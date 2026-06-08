#include "../include/ClassPriorityDeque.h"
#include <stdexcept>

PriorityDeque::PriorityDeque(const initializer_list<int> values)
{
	for (const int value : values)
	{
		insert(value);
	}
}

void PriorityDeque::checkEmpty(void) const
{
	if (isEmpty())
	{
		throw out_of_range("Очередь пуста");
	}
}

void PriorityDeque::insert(const int value)
{
	size_t index = 0;

	while (index < data.size() && data[index] <= value)
	{
		++index;
	}

	data.insert(data.begin() + index, value);
}

int PriorityDeque::removeMin(void)
{
	checkEmpty();

	const int value = data.front();
	data.erase(data.begin());

	return value;
}

int PriorityDeque::removeMax(void)
{
	checkEmpty();

	const int value = data.back();
	data.pop_back();

	return value;
}

int PriorityDeque::getMin(void) const
{
	checkEmpty();

	return data.front();
}

int PriorityDeque::getMax(void) const
{
	checkEmpty();

	return data.back();
}

size_t PriorityDeque::getSize(void) const
{
	return data.size();
}

bool PriorityDeque::isEmpty(void) const
{
	return data.empty();
}

string PriorityDeque::toString(void) const
{
	string result = "[";

	for (size_t i = 0; i < data.size(); ++i)
	{
		result += to_string(data[i]);

		if (i + 1 < data.size())
		{
			result += ", ";
		}
	}

	result += "]";

	return result;
}

PriorityDeque& PriorityDeque::operator << (const int value)
{
	insert(value);

	return *this;
}

PriorityDeque& PriorityDeque::operator >> (int& value)
{
	value = removeMax();

	return *this;
}

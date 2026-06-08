#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>
#include "../include/ClassPriorityDeque.h"

using namespace std;

/**
* @brief Тест конструктора по-умолчанию класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Default_Constructor)
{
	PriorityDeque queue;

	ASSERT_TRUE(queue.isEmpty());
	ASSERT_EQ(queue.getSize(), 0);
	ASSERT_EQ(queue.toString(), "[]");
}

/**
* @brief Тест конструктора со списком инициализации класса очереди с приоритетом
*/
TEST(PriorityDequeTest, InitializerList_Constructor)
{
	PriorityDeque queue = { 5, 1, 4, 2, 3 };

	ASSERT_FALSE(queue.isEmpty());
	ASSERT_EQ(queue.getSize(), 5);
	ASSERT_EQ(queue.toString(), "[1, 2, 3, 4, 5]");
}

/**
* @brief Тест добавления элемента в очередь с приоритетом
*/
TEST(PriorityDequeTest, Insert)
{
	PriorityDeque queue = { 4, 1, 7 };

	queue.insert(5);
	queue.insert(0);

	ASSERT_EQ(queue.toString(), "[0, 1, 4, 5, 7]");
	ASSERT_EQ(queue.getSize(), 5);
}

/**
* @brief Тест получения минимального и максимального приоритета
*/
TEST(PriorityDequeTest, Get_Min_And_Max)
{
	PriorityDeque queue = { 6, 2, 8, 1 };

	ASSERT_EQ(queue.getMin(), 1);
	ASSERT_EQ(queue.getMax(), 8);
}

/**
* @brief Тест удаления элемента с наименьшим приоритетом
*/
TEST(PriorityDequeTest, Remove_Min)
{
	PriorityDeque queue = { 3, 1, 2 };

	ASSERT_EQ(queue.removeMin(), 1);
	ASSERT_EQ(queue.toString(), "[2, 3]");
	ASSERT_EQ(queue.getMin(), 2);
}

/**
* @brief Тест удаления элемента с наибольшим приоритетом
*/
TEST(PriorityDequeTest, Remove_Max)
{
	PriorityDeque queue = { 3, 1, 2 };

	ASSERT_EQ(queue.removeMax(), 3);
	ASSERT_EQ(queue.toString(), "[1, 2]");
	ASSERT_EQ(queue.getMax(), 2);
}

/**
* @brief Тест оператора сдвига влево класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Left_Shift_Operator)
{
	PriorityDeque queue;

	queue << 4;
	queue << 1;
	queue << 3;

	ASSERT_EQ(queue.toString(), "[1, 3, 4]");
}

/**
* @brief Тест оператора сдвига вправо класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Right_Shift_Operator)
{
	PriorityDeque queue = { 6, 2, 8 };
	int value = 0;

	queue >> value;

	ASSERT_EQ(value, 8);
	ASSERT_EQ(queue.toString(), "[2, 6]");
}

/**
* @brief Тест оператора приравнивания класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Assignment_Operator)
{
	PriorityDeque queue = { 4, 2 };
	PriorityDeque copy;

	copy = queue;
	queue.removeMax();

	ASSERT_EQ(copy.toString(), "[2, 4]");
	ASSERT_EQ(queue.toString(), "[2]");
}

/**
* @brief Тест конструктора копирования класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Copy_Constructor)
{
	PriorityDeque queue = { 2, 1, 3 };
	PriorityDeque copy(queue);

	queue.insert(0);

	ASSERT_EQ(copy.toString(), "[1, 2, 3]");
	ASSERT_EQ(queue.toString(), "[0, 1, 2, 3]");
}

/**
* @brief Тест конструктора перемещения класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Move_Constructor)
{
	PriorityDeque queue = { 3, 1, 2 };
	PriorityDeque moved(std::move(queue));

	ASSERT_EQ(moved.toString(), "[1, 2, 3]");
}

/**
* @brief Тест перемещающего оператора приравнивания класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Move_Assignment_Operator)
{
	PriorityDeque queue = { 9, 1, 5 };
	PriorityDeque moved;

	moved = std::move(queue);

	ASSERT_EQ(moved.toString(), "[1, 5, 9]");
}

/**
* @brief Тест исключений при работе с пустой очередью
*/
TEST(PriorityDequeTest, Empty_Queue_Exception)
{
	PriorityDeque queue;

	ASSERT_THROW(queue.getMin(), out_of_range);
	ASSERT_THROW(queue.getMax(), out_of_range);
	ASSERT_THROW(queue.removeMin(), out_of_range);
	ASSERT_THROW(queue.removeMax(), out_of_range);
}

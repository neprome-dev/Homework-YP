#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>
#include "../include/ClassPriorityDeque.h"

using namespace std;

/**
* @brief Тест конструктора по-умолчанию
*/
TEST(PriorityDequeTest, Default_Constructor)
{
	PriorityDeque queue;

	ASSERT_TRUE(queue.isEmpty());
	ASSERT_EQ(queue.getSize(), 0);
	ASSERT_EQ(queue.toString(), "[]");
}

/**
* @brief Тест конструктора со списком инициализации (упорядочивание по приоритету)
*/
TEST(PriorityDequeTest, InitializerList_Constructor)
{
	PriorityDeque queue = { {100, 5}, {200, 1}, {300, 9}, {400, 3} };

	ASSERT_EQ(queue.getSize(), 4);
	ASSERT_EQ(queue.toString(), "[200(1), 400(3), 100(5), 300(9)]");
}

/**
* @brief Тест добавления элементов с упорядочиванием по приоритету
*/
TEST(PriorityDequeTest, Insert_Orders_By_Priority)
{
	PriorityDeque queue;

	queue.insert(10, 5);
	queue.insert(20, 1);
	queue.insert(30, 9);

	ASSERT_EQ(queue.toString(), "[20(1), 10(5), 30(9)]");
}

/**
* @brief Тест поиска элементов с наименьшим и наибольшим приоритетом
*/
TEST(PriorityDequeTest, Get_Min_And_Max)
{
	PriorityDeque queue = { {11, 2}, {22, 8}, {33, 5} };

	ASSERT_EQ(queue.getMin(), 11);
	ASSERT_EQ(queue.getMax(), 22);
	ASSERT_EQ(queue.getMinPriority(), 2);
	ASSERT_EQ(queue.getMaxPriority(), 8);
}

/**
* @brief Тест удаления элемента с наименьшим приоритетом
*/
TEST(PriorityDequeTest, Remove_Min)
{
	PriorityDeque queue = { {10, 2}, {20, 1}, {30, 3} };

	ASSERT_EQ(queue.removeMin(), 20);
	ASSERT_EQ(queue.toString(), "[10(2), 30(3)]");
	ASSERT_EQ(queue.getMin(), 10);
}

/**
* @brief Тест удаления элемента с наибольшим приоритетом
*/
TEST(PriorityDequeTest, Remove_Max)
{
	PriorityDeque queue = { {10, 2}, {20, 1}, {30, 3} };

	ASSERT_EQ(queue.removeMax(), 30);
	ASSERT_EQ(queue.toString(), "[20(1), 10(2)]");
	ASSERT_EQ(queue.getMax(), 10);
}

/**
* @brief Тест оператора сдвига влево (добавление)
*/
TEST(PriorityDequeTest, Left_Shift_Operator)
{
	PriorityDeque queue;

	queue << make_pair(40, 4);
	queue << make_pair(10, 1);
	queue << make_pair(30, 3);

	ASSERT_EQ(queue.toString(), "[10(1), 30(3), 40(4)]");
}

/**
* @brief Тест оператора сдвига вправо (извлечение максимума)
*/
TEST(PriorityDequeTest, Right_Shift_Operator)
{
	PriorityDeque queue = { {60, 6}, {20, 2}, {80, 8} };
	int value = 0;

	queue >> value;

	ASSERT_EQ(value, 80);
	ASSERT_EQ(queue.toString(), "[20(2), 60(6)]");
}

/**
* @brief Тест оператора присваивания (глубокое копирование)
*/
TEST(PriorityDequeTest, Assignment_Operator)
{
	PriorityDeque queue = { {40, 4}, {20, 2} };
	PriorityDeque copy;

	copy = queue;
	queue.removeMax();

	ASSERT_EQ(copy.toString(), "[20(2), 40(4)]");
	ASSERT_EQ(queue.toString(), "[20(2)]");
}

/**
* @brief Тест конструктора копирования (глубокое копирование)
*/
TEST(PriorityDequeTest, Copy_Constructor)
{
	PriorityDeque queue = { {20, 2}, {10, 1}, {30, 3} };
	PriorityDeque copy(queue);

	queue.insert(0, 0);

	ASSERT_EQ(copy.toString(), "[10(1), 20(2), 30(3)]");
	ASSERT_EQ(queue.toString(), "[0(0), 10(1), 20(2), 30(3)]");
}

/**
* @brief Тест конструктора перемещения
*/
TEST(PriorityDequeTest, Move_Constructor)
{
	PriorityDeque queue = { {30, 3}, {10, 1}, {20, 2} };
	PriorityDeque moved(std::move(queue));

	ASSERT_EQ(moved.toString(), "[10(1), 20(2), 30(3)]");
	ASSERT_EQ(queue.getSize(), 0);
}

/**
* @brief Тест перемещающего оператора присваивания
*/
TEST(PriorityDequeTest, Move_Assignment_Operator)
{
	PriorityDeque queue = { {90, 9}, {10, 1}, {50, 5} };
	PriorityDeque moved;

	moved = std::move(queue);

	ASSERT_EQ(moved.toString(), "[10(1), 50(5), 90(9)]");
	ASSERT_EQ(queue.getSize(), 0);
}

/**
* @brief Тест выброса исключения при работе с пустой очередью
*/
TEST(PriorityDequeTest, Empty_Queue_Throws)
{
	PriorityDeque queue;

	ASSERT_THROW(queue.getMin(), std::out_of_range);
	ASSERT_THROW(queue.getMax(), std::out_of_range);
	ASSERT_THROW(queue.removeMin(), std::out_of_range);
	ASSERT_THROW(queue.removeMax(), std::out_of_range);
}

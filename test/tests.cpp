#include <gtest/gtest.h>
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
* @brief Тест добавления элементов с упорядочиванием по приоритету
*/
TEST(PriorityDequeTest, Insert_Orders_By_Priority)
{
	PriorityDeque queue;

	queue.insert("B", 5);
	queue.insert("A", 1);
	queue.insert("C", 9);
	queue.insert("D", 3);

	ASSERT_EQ(queue.getSize(), 4);
	ASSERT_EQ(queue.toString(), "[A(1), D(3), B(5), C(9)]");
}

/**
* @brief Тест получения данных с минимальным и максимальным приоритетом
*/
TEST(PriorityDequeTest, Get_Min_And_Max)
{
	PriorityDeque queue;

	queue.insert("low", 2);
	queue.insert("high", 8);
	queue.insert("mid", 5);

	ASSERT_EQ(queue.getMin(), "low");
	ASSERT_EQ(queue.getMax(), "high");
	ASSERT_EQ(queue.getMinPriority(), 2);
	ASSERT_EQ(queue.getMaxPriority(), 8);
}

/**
* @brief Тест удаления элемента с наименьшим приоритетом
*/
TEST(PriorityDequeTest, Remove_Min)
{
	PriorityDeque queue;

	queue.insert("second", 2);
	queue.insert("first", 1);
	queue.insert("third", 3);

	ASSERT_EQ(queue.removeMin(), "first");
	ASSERT_EQ(queue.toString(), "[second(2), third(3)]");
	ASSERT_EQ(queue.getMin(), "second");
}

/**
* @brief Тест удаления элемента с наибольшим приоритетом
*/
TEST(PriorityDequeTest, Remove_Max)
{
	PriorityDeque queue;

	queue.insert("second", 2);
	queue.insert("first", 1);
	queue.insert("third", 3);

	ASSERT_EQ(queue.removeMax(), "third");
	ASSERT_EQ(queue.toString(), "[first(1), second(2)]");
	ASSERT_EQ(queue.getMax(), "second");
}

/**
* @brief Тест конструктора копирования класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Copy_Constructor)
{
	PriorityDeque queue;
	queue.insert("a", 1);
	queue.insert("b", 2);

	PriorityDeque copy(queue);
	queue.insert("c", 3);

	ASSERT_EQ(copy.toString(), "[a(1), b(2)]");
	ASSERT_EQ(queue.toString(), "[a(1), b(2), c(3)]");
}

/**
* @brief Тест оператора присваивания класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Assignment_Operator)
{
	PriorityDeque queue;
	queue.insert("x", 4);
	queue.insert("y", 2);

	PriorityDeque copy;
	copy = queue;
	queue.removeMax();

	ASSERT_EQ(copy.toString(), "[y(2), x(4)]");
	ASSERT_EQ(queue.toString(), "[y(2)]");
}

/**
* @brief Тест конструктора перемещения класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Move_Constructor)
{
	PriorityDeque queue;
	queue.insert("a", 1);
	queue.insert("b", 2);

	PriorityDeque moved(std::move(queue));

	ASSERT_EQ(moved.toString(), "[a(1), b(2)]");
	ASSERT_EQ(queue.getSize(), 0);
}

/**
* @brief Тест перемещающего оператора присваивания класса очереди с приоритетом
*/
TEST(PriorityDequeTest, Move_Assignment_Operator)
{
	PriorityDeque queue;
	queue.insert("a", 1);
	queue.insert("b", 5);

	PriorityDeque moved;
	moved = std::move(queue);

	ASSERT_EQ(moved.toString(), "[a(1), b(5)]");
	ASSERT_EQ(queue.getSize(), 0);
}

/**
* @brief Тест завершения программы при работе с пустой очередью
*/
TEST(PriorityDequeTest, Empty_Queue_Exit)
{
	PriorityDeque queue;

	EXPECT_EXIT(queue.getMin(), ::testing::ExitedWithCode(1), "Очередь пуста");
	EXPECT_EXIT(queue.getMax(), ::testing::ExitedWithCode(1), "Очередь пуста");
	EXPECT_EXIT(queue.removeMin(), ::testing::ExitedWithCode(1), "Очередь пуста");
	EXPECT_EXIT(queue.removeMax(), ::testing::ExitedWithCode(1), "Очередь пуста");
}

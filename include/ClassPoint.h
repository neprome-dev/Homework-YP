#pragma once

#include <iostream>

using namespace std;

/**
* @brief Класс "Точка"
*/
class Point
{
private:
	/**
	* @param x - координата точки по горизонтальной оси
	*/
	double x;

	/**
	* @param y - координата точки по вертикальной оси
	*/
	double y;
public:
	/**
	* @brief Базовый конструктор класса, меняет значения x и y на указанные пользователем
	* @param x - передаваемое значение по оси x (по умолчанию 0)
	* @param y - передаваемое значение по оси y (по умолчанию 0)
	*/
	Point(const double x = 0, const double y = 0);

	/**
	* @brief Получает значение по оси x у конкретной точки
	* @return Значение по оси x
	*/
	double getX(void) const;

	/**
	* @brief Получает значение по оси y у конкретной точки
	* @return Значение по оси y
	*/
	double getY(void) const;

	/**
	* @brief Оператор приравнивания, присваивает значение координат другой точке
	* @param other - точка, на чьи значения будет происходить замена
	*/
	void operator = (const Point& other);

	/**
	* @brief Оператор равенства, точки считаются равными, если их координаты попарно равны
	* @param other - точка, с которой происходит сравнение
	*/
	bool operator == (const Point& other) const;

	/**
	* @brief Оператор неравенства, точки считаются не равными, если их координаты попарно не равны
	* @param other - точка, с которой происходит сравнение
	*/
	bool operator != (const Point& other) const;

	/**
	* @brief Оператор "меньше", сравнивает точки по абсциссе
	* @param other - точка, с которой происходит сравнение
	*/
	bool operator < (const Point& other) const;

	/**
	* @brief Оператор вывода для класса точка
	* @param output - ссылка на поток вывода
	* @param point - ссылка на выводимую точку
	* @return Координаты точки в формате (x, y)
	*/
	friend ostream& operator << (ostream& output, const Point& point);

	/**
	* @brief Оператор ввода для класса точка
	* @param input - ссылка на поток ввода
	* @param point - ссылка на вводимую точку
	*/
	friend istream& operator >> (istream& input, Point& point);
};

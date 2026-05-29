#pragma once

#include "ClassPoint.h"

#include <iostream>

using namespace std;

/**
* @brief Класс "Отрезок", соединяющий две точки (линейная интерполяция)
*/
class Segment
{
private:
	/**
	* @param left - левая точка отрезка
	*/
	Point left;

	/**
	* @param right - правая точка отрезка
	*/
	Point right;

	/**
	* @brief Проверка на правильное задание отрезка
	*/
	void checkSegment(void);
public:
	/**
	* @brief Базовый конструктор класса, задаёт отрезок двумя точками
	* @param left - левая точка отрезка
	* @param right - правая точка отрезка
	*/
	Segment(const Point left, const Point right);

	/**
	* @brief Получает левую точку отрезка
	* @return Левая точка отрезка
	*/
	Point getLeft(void) const;

	/**
	* @brief Получает правую точку отрезка
	* @return Правая точка отрезка
	*/
	Point getRight(void) const;

	/**
	* @brief Расчёт ординаты по заданной абсциссе методом линейной интерполяции
	* @param x - абсцисса, для которой рассчитывается ордината
	* @return Значение ординаты в точке x
	*/
	double getValue(const double x) const;

	/**
	* @brief Статический метод чтения отрезка из стандартного потока ввода
	* @param input - ссылка на поток ввода
	* @return Считанный отрезок
	*/
	static Segment read(istream& input);

	/**
	* @brief Оператор вывода для класса отрезок
	* @param output - ссылка на поток вывода
	* @param segment - ссылка на выводимый отрезок
	* @return Отрезок в формате [(x1, y1); (x2, y2)]
	*/
	friend ostream& operator << (ostream& output, const Segment& segment);
};

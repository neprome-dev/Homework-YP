#pragma once

#include "ClassPoint.h"

#include <vector>
#include <initializer_list>

using namespace std;

/**
* @brief Абстрактный базовый класс "Кусочно-линейная аппроксимация функции"
*/
class Approximator
{
protected:
	/**
	* @param points - коллекция точек, задающих функцию
	*/
	vector<Point> points;
public:
	/**
	* @brief Базовый конструктор по-умолчанию, создаёт пустую коллекцию точек
	*/
	Approximator(void) = default;

	/**
	* @brief Конструктор, принимающий вектор точек
	* @param points - вектор точек, задающих функцию
	*/
	Approximator(const vector<Point>& points);

	/**
	* @brief Конструктор, принимающий список инициализации точек
	* @param points - список точек, задающих функцию
	*/
	Approximator(const initializer_list<Point> points);

	/**
	* @brief Добавляет точку в коллекцию точек
	* @param point - добавляемая точка
	*/
	void addPoint(const Point& point);

	/**
	* @brief Виртуальная функция расчёта ординаты по заданной абсциссе
	* @param x - абсцисса, для которой рассчитывается ордината
	* @return Значение ординаты в точке x
	*/
	virtual double getValue(const double x) const = 0;

	/**
	* @brief Виртуальный деструктор по-умолчанию
	*/
	virtual ~Approximator() = default;
};

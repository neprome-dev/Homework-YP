#pragma once

#include "ClassApproximator.h"
#include "ClassPoint.h"

#include <vector>
#include <initializer_list>

using namespace std;

/**
* @brief Класс "Линейная интерполяция"
*/
class LinearInterpolator :public Approximator
{
public:
	/**
	* @brief Базовый конструктор по-умолчанию, создаёт пустую коллекцию точек
	*/
	LinearInterpolator(void) = default;

	/**
	* @brief Конструктор, принимающий вектор точек
	* @param points - вектор точек, задающих функцию
	*/
	LinearInterpolator(const vector<Point>& points);

	/**
	* @brief Конструктор, принимающий список инициализации точек
	* @param points - список точек, задающих функцию
	*/
	LinearInterpolator(const initializer_list<Point> points);

	/**
	* @brief Расчёт ординаты по заданной абсциссе методом линейной интерполяции
	* @param x - абсцисса, для которой рассчитывается ордината
	* @return Значение ординаты в точке x
	*/
	double getValue(const double x) const override;
};

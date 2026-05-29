#include <iostream>
#include <vector>
#include <memory>

#include "../include/ClassPoint.h"
#include "../include/ClassSegment.h"
#include "../include/ClassApproximator.h"
#include "../include/ClassLinearInterpolator.h"

using namespace std;

/**
* @brief Считывает число введённое с клавиатуры
* @return Считанное значение
*/
double getNumber();

/**
* @brief Точка входа в программу
* @return Если программа выполнена корректно - 0, иначе 1
*/
int main()
{
	system("chcp 1251");
	system("CLS");

	cout << "Вариант 19\n";
	Segment segment(Point(0, 0), Point(10, 20));
	cout << "Отрезок: " << segment << '\n';
	cout << "Ордината при x = 5: " << segment.getValue(5) << "\n\n";

	cout << "Пример коллекции класса Approximator\n";

	vector<shared_ptr<Approximator>> approximators;
	approximators.push_back(make_shared<LinearInterpolator>(
		initializer_list<Point>{ Point(0, 0), Point(2, 4), Point(4, 8) }));
	approximators.push_back(make_shared<LinearInterpolator>(
		vector<Point>{ Point(0, 1), Point(5, 6), Point(10, 1) }));

	for (const auto& approximator : approximators)
	{
		cout << "Значение в точке x = 3: " << approximator->getValue(3) << '\n';
	}

	cout << "\nВведите абсциссу для расчёта ординаты: ";
	double x = getNumber();
	cout << "Ордината: " << approximators[0]->getValue(x) << '\n';

	return 0;
}

double getNumber()
{
	double number = 0;
	cin >> number;

	if (cin.fail())
	{
		cerr << "Ошибка чтения" << endl;
		exit(1);
	}

	return number;
}


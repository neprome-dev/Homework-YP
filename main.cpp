#include <iostream>
#include <stdexcept>

#include "Point.h"
#include "Rectangle.h"

bool InputPoint(Point& point)
{
    double x;
    double y;

    if (!(std::cin >> x >> y))
    {
        return false;
    }

    point = Point(x, y);
    return true;
}

int main()
{
    Point p1;
    Point p2;
    Point p3;
    Point p4;

    std::cout << "Введите координаты 4 точек прямоугольника:" << std::endl;

    if (!InputPoint(p1) || !InputPoint(p2) || !InputPoint(p3) || !InputPoint(p4))
    {
        std::cout << "Ошибка ввода данных" << std::endl;
        return 1;
    }

    try
    {
        Rectangle rectangle(p1, p2, p3, p4);

        rectangle.Show();

        std::cout << "Периметр: " << rectangle.Perimeter() << std::endl;
        std::cout << "Площадь: " << rectangle.Area() << std::endl;
    }
    catch (const std::invalid_argument& error)
    {
        std::cout << "Ошибка: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}

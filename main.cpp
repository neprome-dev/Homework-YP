#include <iostream>
#include <stdexcept>

#include "Point.h"
#include "Rectangle.h"

/**
 * @brief Считывает координаты точки из стандартного ввода.
 * @return Точка с введёнными координатами.
 */
Point InputPoint();

int main()
{
    std::cout << "Введите координаты 4 точек прямоугольника:" << std::endl;

    const Point p1 = InputPoint();
    const Point p2 = InputPoint();
    const Point p3 = InputPoint();
    const Point p4 = InputPoint();

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

Point InputPoint()
{
    double x = 0.0;
    double y = 0.0;

    if (!(std::cin >> x >> y))
    {
        exit(1);
    }

    return Point(x, y);
}

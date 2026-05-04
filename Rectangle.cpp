#include "Rectangle.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle()
{
    p1 = Point(0.0, 0.0);
    p2 = Point(1.0, 0.0);
    p3 = Point(1.0, 1.0);
    p4 = Point(0.0, 1.0);
}

Rectangle::Rectangle(const Point& point1, const Point& point2,
                     const Point& point3, const Point& point4)
{
    p1 = point1;
    p2 = point2;
    p3 = point3;
    p4 = point4;

    if (!isRectangle())
    {
        throw std::invalid_argument("Точки не задают прямоугольник");
    }
}

double Rectangle::getSideLength(const Point& first, const Point& second) const
{
    const double dx = second.getX() - first.getX();
    const double dy = second.getY() - first.getY();

    return std::sqrt(dx * dx + dy * dy);
}

bool Rectangle::isRectangle() const
{
    const double eps = 1e-9;

    const double abX = p2.getX() - p1.getX();
    const double abY = p2.getY() - p1.getY();

    const double bcX = p3.getX() - p2.getX();
    const double bcY = p3.getY() - p2.getY();

    const double cdX = p4.getX() - p3.getX();
    const double cdY = p4.getY() - p3.getY();

    const double daX = p1.getX() - p4.getX();
    const double daY = p1.getY() - p4.getY();

    const double abLength = getSideLength(p1, p2);
    const double bcLength = getSideLength(p2, p3);

    if (abLength < eps || bcLength < eps)
    {
        return false;
    }

    const double scalar = abX * bcX + abY * bcY;

    const bool hasRightAngle = std::fabs(scalar) < eps;

    const bool oppositeSidesEqual = std::fabs(abX + cdX) < eps &&
                                    std::fabs(abY + cdY) < eps &&
                                    std::fabs(bcX + daX) < eps &&
                                    std::fabs(bcY + daY) < eps;

    return hasRightAngle && oppositeSidesEqual;
}

void Rectangle::Show() const
{
    std::cout << "Point 1: " << p1.getX() << " " << p1.getY() << std::endl;
    std::cout << "Point 2: " << p2.getX() << " " << p2.getY() << std::endl;
    std::cout << "Point 3: " << p3.getX() << " " << p3.getY() << std::endl;
    std::cout << "Point 4: " << p4.getX() << " " << p4.getY() << std::endl;
}

double Rectangle::Perimeter() const
{
    const double a = getSideLength(p1, p2);
    const double b = getSideLength(p2, p3);

    return 2.0 * (a + b);
}

double Rectangle::Area() const
{
    const double a = getSideLength(p1, p2);
    const double b = getSideLength(p2, p3);

    return a * b;
}

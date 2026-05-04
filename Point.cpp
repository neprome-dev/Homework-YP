#include "Point.h"

Point::Point()
{
    x = 0.0;
    y = 0.0;
}

Point::Point(double newX, double newY)
{
    x = newX;
    y = newY;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

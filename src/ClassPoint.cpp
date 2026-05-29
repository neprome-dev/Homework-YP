#include "../include/ClassPoint.h"
#include "../include/ClassMathHelper.h"

Point::Point(const double x, const double y)
{
	this->x = x;
	this->y = y;
}

double Point::getX(void) const
{
	return x;
}

double Point::getY(void) const
{
	return y;
}

void Point::operator = (const Point& other)
{
	this->x = other.x;
	this->y = other.y;
}

bool Point::operator == (const Point& other) const
{
	return (MathHelper::isEqual(this->x, other.x) && MathHelper::isEqual(this->y, other.y));
}

bool Point::operator != (const Point& other) const
{
	return !(*this == other);
}

bool Point::operator < (const Point& other) const
{
	return this->x < other.x;
}

ostream& operator << (ostream& output, const Point& point)
{
	output << "(" << point.x << ", " << point.y << ")";
	return output;
}

istream& operator >> (istream& input, Point& point)
{
	double x = 0;
	double y = 0;
	input >> x >> y;
	if (input.fail())
	{
		cerr << "Ошибка чтения" << endl;
		exit(1);
	}

	point.x = x;
	point.y = y;

	return input;
}

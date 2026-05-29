#include "../include/ClassApproximator.h"

Approximator::Approximator(const vector<Point>& points)
{
	this->points = points;
}

Approximator::Approximator(const initializer_list<Point> points)
{
	this->points = vector<Point>(points);
}

void Approximator::addPoint(const Point& point)
{
	points.push_back(point);
}

#include "../include/ClassLinearInterpolator.h"
#include "../include/ClassSegment.h"

#include <iostream>

using namespace std;

LinearInterpolator::LinearInterpolator(const vector<Point>& points)
	:Approximator(points)
{
}

LinearInterpolator::LinearInterpolator(const initializer_list<Point> points)
	:Approximator(points)
{
}

double LinearInterpolator::getValue(const double x) const
{
	if (points.size() < 2)
	{
		cerr << "Error: Недостаточно точек для интерполяции" << endl;
		exit(1);
	}

	for (size_t i = 0; i + 1 < points.size(); ++i)
	{
		if (x >= points[i].getX() && x <= points[i + 1].getX())
		{
			Segment segment(points[i], points[i + 1]);
			return segment.getValue(x);
		}
	}

	cerr << "Error: Абсцисса лежит вне диапазона интерполяции" << endl;
	exit(1);
}

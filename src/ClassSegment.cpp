#include "../include/ClassSegment.h"

#include <iostream>

using namespace std;

Segment::Segment(const Point left, const Point right)
{
	this->left = left;
	this->right = right;

	checkSegment();
}

void Segment::checkSegment(void)
{
	if (left.getX() == right.getX())
	{
		cerr << "Error: Точки не образуют отрезок" << endl;
		exit(1);
	}
}

Point Segment::getLeft(void) const
{
	return left;
}

Point Segment::getRight(void) const
{
	return right;
}

double Segment::getValue(const double x) const
{
	return left.getY() + (right.getY() - left.getY()) * (x - left.getX()) / (right.getX() - left.getX());
}

Segment Segment::read(istream& input)
{
	Point left;
	Point right;
	input >> left >> right;

	return Segment(left, right);
}

ostream& operator << (ostream& output, const Segment& segment)
{
	output << "[" << segment.left << "; " << segment.right << "]";
	return output;
}

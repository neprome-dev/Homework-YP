#include <gtest/gtest.h>

#include "../include/ClassPoint.h"
#include "../include/ClassSegment.h"
#include "../include/ClassApproximator.h"
#include "../include/ClassLinearInterpolator.h"

#include <sstream>
#include <vector>
#include <cfloat>
#include <cmath>

using namespace std;

/**
* @brief Тест операторов ==; !=; =; класса точки
*/
TEST(PointTest, Basic_Operators)
{
	Point P1(10, 20);
	Point P2(10, 20);
	Point P3(20, 20);

	ASSERT_TRUE(P1 == P2);
	ASSERT_TRUE(P1 != P3);

	P1 = P3;
	ASSERT_TRUE(P1 == P3);
}

/**
* @brief Тест оператора "меньше" класса точки
*/
TEST(PointTest, Less_Operator)
{
	Point P1(10, 50);
	Point P2(20, 5);

	ASSERT_TRUE(P1 < P2);
	ASSERT_FALSE(P2 < P1);
}

/**
* @brief Тест операторов <<; >>; класса точки
*/
TEST(PointTest, IO_Operators)
{
	stringstream input("10 20");
	Point P;
	input >> P;

	ASSERT_EQ(P.getX(), 10);
	ASSERT_EQ(P.getY(), 20);

	stringstream output;
	output << P;
	ASSERT_EQ(output.str(), "(10, 20)");
}

/**
* @brief Тест расчёта ординаты класса отрезок
*/
TEST(SegmentTest, GetValue)
{
	Segment segment(Point(0, 0), Point(10, 20));

	ASSERT_TRUE(fabs(segment.getValue(0) - 0) <= DBL_EPSILON);
	ASSERT_TRUE(fabs(segment.getValue(5) - 10) <= DBL_EPSILON);
	ASSERT_TRUE(fabs(segment.getValue(10) - 20) <= DBL_EPSILON);
}

/**
* @brief Тест оператора сдвига влево класса отрезок
*/
TEST(SegmentTest, Output_Operator)
{
	Segment segment(Point(0, 0), Point(10, 20));

	stringstream output;
	output << segment;
	ASSERT_EQ(output.str(), "[(0, 0); (10, 20)]");
}

/**
* @brief Тест статического метода чтения класса отрезок
*/
TEST(SegmentTest, Read)
{
	stringstream input("0 0 10 20");
	Segment segment = Segment::read(input);

	ASSERT_TRUE(segment.getLeft() == Point(0, 0));
	ASSERT_TRUE(segment.getRight() == Point(10, 20));
}

/**
* @brief Тест линейной интерполяции на векторе точек
*/
TEST(LinearInterpolatorTest, Vector_Constructor)
{
	vector<Point> points{ Point(0, 0), Point(2, 4), Point(4, 8) };
	LinearInterpolator interpolator(points);

	ASSERT_TRUE(fabs(interpolator.getValue(1) - 2) <= DBL_EPSILON);
	ASSERT_TRUE(fabs(interpolator.getValue(3) - 6) <= DBL_EPSILON);
}

/**
* @brief Тест линейной интерполяции на списке инициализации
*/
TEST(LinearInterpolatorTest, InitializerList_Constructor)
{
	LinearInterpolator interpolator{ Point(0, 1), Point(5, 6), Point(10, 1) };

	ASSERT_TRUE(fabs(interpolator.getValue(0) - 1) <= DBL_EPSILON);
	ASSERT_TRUE(fabs(interpolator.getValue(5) - 6) <= DBL_EPSILON);
	ASSERT_TRUE(fabs(interpolator.getValue(10) - 1) <= DBL_EPSILON);
}

/**
* @brief Тест добавления точки в коллекцию
*/
TEST(LinearInterpolatorTest, AddPoint)
{
	LinearInterpolator interpolator;
	interpolator.addPoint(Point(0, 0));
	interpolator.addPoint(Point(10, 10));

	ASSERT_TRUE(fabs(interpolator.getValue(5) - 5) <= DBL_EPSILON);
}

#pragma once

#include "Point.h"

/**
 * @brief Класс для работы с прямоугольником на плоскости.
 */
class Rectangle
{
private:
    Point p1;
    Point p2;
    Point p3;
    Point p4;

    /**
     * @brief Вычисляет длину стороны между двумя точками.
     * @param first - первая точка.
     * @param second - вторая точка.
     * @return Длина отрезка между точками.
     */
    double getSideLength(const Point& first, const Point& second) const;

    /**
     * @brief Проверяет, что точки задают прямоугольник.
     * @return true, если точки задают прямоугольник, иначе false.
     */
    bool isRectangle() const;

public:
    /**
     * @brief Конструктор без параметров.
     */
    Rectangle();

    /**
     * @brief Конструктор с параметрами.
     * @param point1 - первая точка прямоугольника.
     * @param point2 - вторая точка прямоугольника.
     * @param point3 - третья точка прямоугольника.
     * @param point4 - четвертая точка прямоугольника.
     */
    Rectangle(const Point& point1, const Point& point2,
              const Point& point3, const Point& point4);

    /**
     * @brief Выводит координаты точек прямоугольника.
     */
    void Show() const;

    /**
     * @brief Вычисляет периметр прямоугольника.
     * @return Периметр прямоугольника.
     */
    double Perimeter() const;

    /**
     * @brief Вычисляет площадь прямоугольника.
     * @return Площадь прямоугольника.
     */
    double Area() const;
};

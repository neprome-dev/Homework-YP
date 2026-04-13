#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Rectangle
{
private:
    double x1, y1, x2, y2, x3, y3, x4, y4;

public:
    /*
    * @brief Конструктор без параметров
    */
    Rectangle();

    /*
    * @brief Конструктор с параметрами
    * @param a1 - x первой точки
    * @param b1 - y первой точки
    * @param a2 - x второй точки
    * @param b2 - y второй точки
    * @param a3 - x третьей точки
    * @param b3 - y третьей точки
    * @param a4 - x четвертой точки
    * @param b4 - y четвертой точки
    */
    Rectangle(double a1, double b1, double a2, double b2,
        double a3, double b3, double a4, double b4);

    /*
    * @brief Выводит координаты точек прямоугольника
    */
    void Show();

    /*
    * @brief Вычисляет периметр прямоугольника
    * @return Периметр прямоугольника
    */
    double Perimeter();

    /*
    * @brief Вычисляет площадь прямоугольника
    * @return Площадь прямоугольника
    */
    double Area();
};

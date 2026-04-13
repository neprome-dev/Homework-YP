#include "Rectangle.h"

/*
* @brief Конструктор без параметров
*/
Rectangle::Rectangle()
{
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
    x3 = 0;
    y3 = 0;
    x4 = 0;
    y4 = 0;
}

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
Rectangle::Rectangle(double a1, double b1, double a2, double b2,
    double a3, double b3, double a4, double b4)
{
    x1 = a1;
    y1 = b1;
    x2 = a2;
    y2 = b2;
    x3 = a3;
    y3 = b3;
    x4 = a4;
    y4 = b4;
}

/*
* @brief Выводит координаты точек прямоугольника
*/
void Rectangle::Show()
{
    cout << "Point 1: " << x1 << " " << y1 << endl;
    cout << "Point 2: " << x2 << " " << y2 << endl;
    cout << "Point 3: " << x3 << " " << y3 << endl;
    cout << "Point 4: " << x4 << " " << y4 << endl;
}

/*
* @brief Вычисляет периметр прямоугольника
* @return Периметр прямоугольника
*/
double Rectangle::Perimeter()
{
    double a, b;

    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

    return 2 * (a + b);
}

/*
* @brief Вычисляет площадь прямоугольника
* @return Площадь прямоугольника
*/
double Rectangle::Area()
{
    double a, b;

    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

    return a * b;
}

#include <iostream>
#include "Rectangle.h"

using namespace std;
// Класс Точка
class Point {
public:
    double x, y;
};

// Функция ввода точки
Point InputPoint(const char* text) {
    Point p;
    cout << text;
    cin >> p.x >> p.y;
    return p;
}

/*
* @brief Точка входа в программу
* @return 0, если программа выполнена верно
*/
int main() {
    Point p1 = InputPoint("Введите x1 y1: ");
    Point p2 = InputPoint("Введите x2 y2: ");
    Point p3 = InputPoint("Введите x3 y3: ");
    Point p4 = InputPoint("Введите x4 y4: ");
    if (cin.fail()) {
        cout << "Ошибка ввода" << endl;
        return 1;
    }

    Rectangle r(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);

    r.Show();
    cout << "P = " << r.Perimeter() << endl;
    cout << "S = " << r.Area() << endl;

    return 0;
}
}

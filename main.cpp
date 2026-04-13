#include <iostream>
#include "Rectangle.h"

using namespace std;

/*
* @brief Точка входа в программу
* @return 0, если программа выполнена верно
*/
int main()
{
    double x1, y1, x2, y2, x3, y3, x4, y4;

    cout << "Input x1 y1: ";
    cin >> x1 >> y1;
    cout << "Input x2 y2: ";
    cin >> x2 >> y2;
    cout << "Input x3 y3: ";
    cin >> x3 >> y3;
    cout << "Input x4 y4: ";
    cin >> x4 >> y4;

    Rectangle r(x1, y1, x2, y2, x3, y3, x4, y4);

    r.Show();
    cout << "P = " << r.Perimeter() << endl;
    cout << "S = " << r.Area() << endl;

    return 0;
}

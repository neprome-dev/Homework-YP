#pragma once

/**
 * @brief Класс для хранения координат точки на плоскости.
 */
class Point
{
private:
    double x;
    double y;

public:
    /**
     * @brief Конструктор без параметров.
     */
    Point();

    /**
     * @brief Конструктор с параметрами.
     * @param newX - координата точки по оси X.
     * @param newY - координата точки по оси Y.
     */
    Point(double newX, double newY);

    /**
     * @brief Возвращает координату точки по оси X.
     * @return Координата X.
     */
    double getX() const;

    /**
     * @brief Возвращает координату точки по оси Y.
     * @return Координата Y.
     */
    double getY() const;
};

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "../include/Matrix.h"
#include "../include/Generator.h"
#include "../include/RandomGenerator.h"
#include "../include/IStreamGenerator.h"
#include "../include/ConstantGenerator.h"
#include "../include/ZeroGenerator.h"
#include "../include/Task1.h"
#include "../include/Task2.h"

using namespace miit::algebra;

/**
 * @brief Варианты выбора способа заполнения матрицы
 */
enum FillMode
{
    RANDOM_FILL = 1,
    KEYBOARD_FILL,
    CONSTANT_FILL,
    ZERO_FILL
};

/**
 * @brief Получить целое число
 * @param message Сообщение перед вводом
 * @return Введённое целое число
 * @throw std::invalid_argument Указатель на сообщение равен nullptr или не введено целое число
 */
int readInteger(const char* message);

/**
 * @brief Получить положительный размер
 * @param message Сообщение перед вводом
 * @return Введённый положительный размер
 * @throw std::invalid_argument Указатель на сообщение равен nullptr или не введено положительное целое число
 */
std::size_t readPositiveSize(const char* message);

/**
 * @brief Выполнить оба задания с выбранным генератором
 * @param rows Количество строк матрицы
 * @param columns Количество столбцов матрицы
 * @param generator Генератор для заполнения матриц
 */
void executeTasks(
    const std::size_t rows,
    const std::size_t columns,
    const Generator& generator);

/**
 * @brief Точка входа в программу
 * @return Ноль при успешном выполнении, иначе единица
 */
int main()
{
    try
    {
        const std::size_t rows = readPositiveSize("Количество строк: ");
        const std::size_t columns = readPositiveSize("Количество столбцов: ");

        std::cout
            << "Способ заполнения:\n"
            << RANDOM_FILL << " - случайные числа\n"
            << KEYBOARD_FILL << " - ввод с клавиатуры\n"
            << CONSTANT_FILL << " - постоянное значение\n"
            << ZERO_FILL << " - нули\n";

        switch (readInteger("Ваш выбор: "))
        {
        case RANDOM_FILL:
        {
            const int minimum = readInteger("Минимальное значение: ");
            const int maximum = readInteger("Максимальное значение: ");
            const RandomGenerator generator(minimum, maximum);
            executeTasks(rows, columns, generator);
            break;
        }
        case KEYBOARD_FILL:
        {
            const std::size_t elementCount = rows * columns;
            std::cout
                << "Введите " << elementCount << " целых чисел для задания 1,\n"
                << "затем столько же чисел для задания 2:\n";
            const IStreamGenerator generator(std::cin);
            executeTasks(rows, columns, generator);
            break;
        }
        case CONSTANT_FILL:
        {
            const int value = readInteger("Значение: ");
            const ConstantGenerator generator(value);
            executeTasks(rows, columns, generator);
            break;
        }
        case ZERO_FILL:
        {
            const ZeroGenerator generator;
            executeTasks(rows, columns, generator);
            break;
        }
        default:
            throw std::invalid_argument("Неизвестный способ заполнения");
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

int readInteger(const char* message)
{
    if (message == nullptr)
    {
        throw std::invalid_argument("Не указано сообщение для ввода");
    }
    std::cout << message;

    int value = 0;
    if (!(std::cin >> value))
    {
        throw std::invalid_argument("Нужно ввести целое число");
    }

    return value;
}

std::size_t readPositiveSize(const char* message)
{
    if (message == nullptr)
    {
        throw std::invalid_argument("Не указано сообщение для ввода");
    }
    const int value = readInteger(message);
    if (value <= 0)
    {
        throw std::invalid_argument("Размер должен быть положительным");
    }

    return static_cast<std::size_t>(value);
}

void executeTasks(
    const std::size_t rows,
    const std::size_t columns,
    const Generator& generator)
{
    Matrix<int> firstMatrix(rows, columns);
    Task1 task1(firstMatrix, generator);

    std::cout << "\nИсходная матрица для задания 1:\n" << firstMatrix << '\n';
    std::cout << "\nРезультат задания 1:\n" << task1.Solve() << '\n';

    Matrix<int> secondMatrix(rows, columns);
    Task2 task2(secondMatrix, generator);

    std::cout << "\nИсходная матрица для задания 2:\n" << secondMatrix << '\n';
    std::cout << "\nРезультат задания 2:\n" << task2.Solve() << '\n';
}

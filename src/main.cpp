#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
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
 */
int readInteger(const char* message);

/**
 * @brief Получить положительный размер
 * @param message Сообщение перед вводом
 * @return Введённый положительный размер
 */
std::size_t readPositiveSize(const char* message);

/**
 * @brief Выбрать генератор для заполнения матрицы
 * @param elementCount Количество элементов, которые нужно ввести с клавиатуры
 * @return Указатель на выбранный генератор
 */
std::unique_ptr<Generator> chooseGenerator(std::size_t elementCount);

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
        auto generator = chooseGenerator(rows * columns);

        Matrix<int> matrix(rows, columns);
        Task1 task1(matrix, *generator);
        Task2 task2(matrix, *generator);

        task1.Fill();

        std::cout << "\nИсходная матрица:\n" << matrix << '\n';
        std::cout << "\nЗадание 1:\n" << task1.Solve() << '\n';
        std::cout << "\nЗадание 2:\n" << task2.Solve() << '\n';
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
    for (;;)
    {
        std::cout << message;
        int value = 0;
        if (std::cin >> value)
        {
            return value;
        }

        if (std::cin.eof())
        {
            throw std::runtime_error("Ввод завершён");
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Нужно ввести целое число. Повторите ввод.\n";
    }
}

std::size_t readPositiveSize(const char* message)
{
    for (;;)
    {
        const int value = readInteger(message);
        if (value > 0)
        {
            return static_cast<std::size_t>(value);
        }
        std::cout << "Размер должен быть положительным.\n";
    }
}

std::unique_ptr<Generator> chooseGenerator(const std::size_t elementCount)
{
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
        return std::make_unique<RandomGenerator>(minimum, maximum);
    }
    case KEYBOARD_FILL:
        std::cout << "Введите " << elementCount << " целых чисел:\n";
        return std::make_unique<IStreamGenerator>(std::cin);
    case CONSTANT_FILL:
        return std::make_unique<ConstantGenerator>(readInteger("Значение: "));
    case ZERO_FILL:
        return std::make_unique<ZeroGenerator>();
    default:
        throw std::invalid_argument("Неизвестный способ заполнения");
    }
}

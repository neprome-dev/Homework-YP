#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "ZeroGenerator.h"

#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

using namespace miit::algebra;

namespace
{
    int readInteger(const char* prompt)
    {
        for (;;)
        {
            std::cout << prompt;
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

    std::size_t readPositiveSize(const char* prompt)
    {
        for (;;)
        {
            const int value = readInteger(prompt);
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
            << "1 - случайные числа\n"
            << "2 - ввод с клавиатуры\n"
            << "3 - постоянное значение\n"
            << "4 - нули\n";

        switch (readInteger("Ваш выбор: "))
        {
        case 1:
        {
            const int minimum = readInteger("Минимальное значение: ");
            const int maximum = readInteger("Максимальное значение: ");
            return std::make_unique<RandomGenerator>(minimum, maximum);
        }
        case 2:
            std::cout << "Введите " << elementCount << " целых чисел:\n";
            return std::make_unique<IStreamGenerator>(std::cin);
        case 3:
            return std::make_unique<ConstantGenerator>(readInteger("Значение: "));
        case 4:
            return std::make_unique<ZeroGenerator>();
        default:
            throw std::invalid_argument("Неизвестный способ заполнения");
        }
    }
}

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

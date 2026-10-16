#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный интерфейс генератора целых значений.
     */
    class Generator
    {
    public:
        Generator() = default;
        Generator(const Generator&) = default;
        Generator(Generator&&) noexcept = default;
        Generator& operator=(const Generator&) = default;
        Generator& operator=(Generator&&) noexcept = default;

        virtual ~Generator();

        /**
         * @brief Получить следующее значение для заполнения матрицы.
         */
        virtual int generate() const = 0;
    };
}

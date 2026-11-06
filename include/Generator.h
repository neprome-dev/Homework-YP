#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный интерфейс для генерации значений при заполнении матрицы
     */
    class Generator
    {
    public:
        /**
         * @brief Уничтожить объект генератора
         */
        virtual ~Generator() = default;

        /**
         * @brief Сгенерировать следующее значение
         * @return Сгенерированное значение
         */
        virtual int generate() const = 0;
    };
}

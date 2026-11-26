#pragma once

#include <string>

namespace miit::kindergarten
{
    /**
     * @brief Базовый класс для воспитанников и педагогов
     */
    class KindergartenPerson
    {
    private:
        /**
         * @brief Полное имя человека
         */
        std::string fullName_;

    protected:
        /**
         * @brief Сохранить полное имя человека
         * @param fullName Фамилия, имя и отчество
         * @throw std::invalid_argument Если ФИО пустое
         */
        explicit KindergartenPerson(const std::string& fullName);

    public:
        /**
         * @brief Уничтожить объект базового или производного класса
         */
        virtual ~KindergartenPerson();

        /**
         * @brief Получить полное имя
         * @return Фамилия, имя и отчество
         */
        const std::string& getFullName() const noexcept;

        /**
         * @brief Получить текстовое описание человека
         * @return Описание воспитанника или педагога
         */
        virtual std::string getDescription() const = 0;
    };
}

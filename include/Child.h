#pragma once

#include <string>

#include "KindergartenPerson.h"

namespace miit::kindergarten
{
    /**
     * @brief Пол ребёнка
     */
    enum class Gender
    {
        Boy,
        Girl
    };

    /**
     * @brief Воспитанник детского сада
     */
    class Child : public KindergartenPerson
    {
    private:
        /**
         * @brief Возраст ребёнка в полных годах
         */
        int age_;

        /**
         * @brief Пол ребёнка
         */
        Gender gender_;

        /**
         * @brief Название группы, которую посещает ребёнок
         */
        std::string groupName_;

    public:
        /**
         * @brief Создать запись о воспитаннике
         * @param fullName Фамилия, имя и отчество
         * @param age Возраст в полных годах от 2 до 7 включительно
         * @param gender Пол ребёнка
         * @param groupName Название группы
         * @throw std::invalid_argument Если ФИО или название группы пустое либо возраст вне диапазона
         */
        Child(const std::string& fullName, const int age, const Gender gender,
              const std::string& groupName);

        /**
         * @brief Получить возраст ребёнка
         * @return Возраст в полных годах
         */
        int getAge() const noexcept;

        /**
         * @brief Получить пол ребёнка
         * @return Пол ребёнка
         */
        Gender getGender() const noexcept;

        /**
         * @brief Получить название группы ребёнка
         * @return Название группы
         */
        const std::string& getGroupName() const noexcept;

        /**
         * @brief Составить описание воспитанника
         * @return ФИО, возраст и название группы
         */
        std::string getDescription() const override;
    };
}

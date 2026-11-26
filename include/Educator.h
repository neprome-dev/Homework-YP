#pragma once

#include <string>

#include "KindergartenPerson.h"

namespace miit::kindergarten
{
    /**
     * @brief Педагог детского сада
     */
    class Educator : public KindergartenPerson
    {
    private:
        /**
         * @brief Номер педагога для связи с расписанием
         */
        int id_;

    public:
        /**
         * @brief Создать запись о педагоге
         * @param fullName Фамилия, имя и отчество
         * @param id Положительный номер педагога
         * @throw std::invalid_argument Если ФИО пустое либо номер неположительный
         */
        Educator(const std::string& fullName, const int id);

        /**
         * @brief Получить номер педагога
         * @return Номер педагога
         */
        int getId() const noexcept;

        /**
         * @brief Составить описание педагога
         * @return ФИО и номер педагога
         */
        std::string getDescription() const override;
    };
}

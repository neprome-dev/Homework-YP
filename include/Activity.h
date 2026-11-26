#pragma once

#include <string>

namespace miit::kindergarten
{
    /**
     * @brief Дни недели в календарном порядке
     */
    enum class DayOfWeek
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    /**
     * @brief Виды занятий и прогулок в расписании
     */
    enum class ActivityType
    {
        Music,
        PhysicalEducation,
        Drawing,
        Walk
    };

    /**
     * @brief Одна запись в недельном расписании детского сада
     */
    class Activity
    {
    private:
        /**
         * @brief Название группы
         */
        std::string groupName_;

        /**
         * @brief День недели
         */
        DayOfWeek day_;

        /**
         * @brief Минута начала, отсчитанная от полуночи
         */
        int startMinute_;

        /**
         * @brief Минута окончания, отсчитанная от полуночи
         */
        int endMinute_;

        /**
         * @brief Вид занятия или прогулка
         */
        ActivityType type_;

        /**
         * @brief Номер ответственного педагога
         */
        int educatorId_;

    public:
        /**
         * @brief Создать запись на заданное время
         * @param groupName Название группы
         * @param day День недели
         * @param startMinute Минута начала от полуночи
         * @param endMinute Минута окончания от полуночи
         * @param type Вид занятия или прогулка
         * @param educatorId Положительный номер ответственного педагога
         * @throw std::invalid_argument Если название, день, вид, время или номер недопустимы
         */
        Activity(const std::string& groupName, const DayOfWeek day, const int startMinute,
                 const int endMinute, const ActivityType type, const int educatorId);

        /**
         * @brief Получить название группы
         * @return Название группы
         */
        const std::string& getGroupName() const noexcept;

        /**
         * @brief Получить день недели
         * @return День недели
         */
        DayOfWeek getDay() const noexcept;

        /**
         * @brief Получить время начала
         * @return Количество минут от полуночи
         */
        int getStartMinute() const noexcept;

        /**
         * @brief Получить время окончания
         * @return Количество минут от полуночи
         */
        int getEndMinute() const noexcept;

        /**
         * @brief Получить вид записи расписания
         * @return Вид занятия или прогулка
         */
        ActivityType getType() const noexcept;

        /**
         * @brief Получить номер ответственного педагога
         * @return Номер педагога
         */
        int getEducatorId() const noexcept;

        /**
         * @brief Получить место проведения по виду записи
         * @return Название отдельного помещения или площадки для прогулок
         */
        std::string getPlace() const;
    };
}

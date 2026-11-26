#pragma once

#include <string>
#include <vector>

#include "Activity.h"
#include "Child.h"
#include "Educator.h"

namespace miit::kindergarten
{
    /**
     * @brief Группы, воспитанники, педагоги и расписание детского сада
     */
    class Kindergarten
    {
    private:
        /**
         * @brief Названия зарегистрированных групп
         */
        std::vector<std::string> groupNames_;

        /**
         * @brief Воспитанники детского сада
         */
        std::vector<Child> children_;

        /**
         * @brief Педагоги детского сада
         */
        std::vector<Educator> educators_;

        /**
         * @brief Записи недельного расписания
         */
        std::vector<Activity> activities_;

        /**
         * @brief Проверить, зарегистрирована ли группа
         * @param groupName Название группы
         * @return true, если группа существует
         */
        bool hasGroup(const std::string& groupName) const;

        /**
         * @brief Проверить, зарегистрирован ли педагог
         * @param educatorId Номер педагога
         * @return true, если педагог существует
         */
        bool hasEducator(const int educatorId) const noexcept;

    public:
        /**
         * @brief Добавить группу
         * @param groupName Название группы
         * @throw std::invalid_argument Если название пустое или уже занято
         */
        void addGroup(const std::string& groupName);

        /**
         * @brief Добавить воспитанника в его группу
         * @param child Объект класса Child
         * @throw std::invalid_argument Если группа воспитанника не зарегистрирована
         */
        void addChild(const Child& child);

        /**
         * @brief Зарегистрировать педагога
         * @param educator Объект класса Educator
         * @throw std::invalid_argument Если номер педагога уже занят
         */
        void addEducator(const Educator& educator);

        /**
         * @brief Добавить запись в недельное расписание
         * @param activity Объект класса Activity
         * @throw std::invalid_argument Если группа или педагог неизвестны либо есть пересечение по времени
         */
        void addActivity(const Activity& activity);

        /**
         * @brief Получить список всех воспитанников
         * @return Список воспитанников
         */
        const std::vector<Child>& getChildren() const noexcept;

        /**
         * @brief Получить список всех педагогов
         * @return Список педагогов
         */
        const std::vector<Educator>& getEducators() const noexcept;

        /**
         * @brief Выбрать воспитанников указанной группы
         * @param groupName Название группы
         * @return Список воспитанников указанной группы
         */
        std::vector<Child> getChildrenByGroup(const std::string& groupName) const;

        /**
         * @brief Выбрать воспитанников указанного возраста
         * @param age Возраст в полных годах
         * @return Список воспитанников указанного возраста
         */
        std::vector<Child> getChildrenByAge(const int age) const;

        /**
         * @brief Получить недельную занятость педагога
         * @param educatorId Номер педагога
         * @return Записи расписания по дням и времени начала
         */
        std::vector<Activity> getEducatorSchedule(const int educatorId) const;

        /**
         * @brief Получить расписание группы на выбранный день
         * @param groupName Название группы
         * @param day День недели
         * @return Записи группы по времени начала
         */
        std::vector<Activity> getGroupSchedule(const std::string& groupName,
                                               const DayOfWeek day) const;

        /**
         * @brief Рассчитать долю мальчиков или девочек в группе
         * @param groupName Название группы
         * @param gender Пол, для которого считают долю
         * @return Процент от числа детей в группе или 0 для пустой группы
         */
        double getGenderPercentage(const std::string& groupName, const Gender gender) const;

        /**
         * @brief Найти группы воспитанников по точному ФИО
         * @param fullName Фамилия, имя и отчество ребёнка
         * @return Все подходящие названия групп без повторений
         */
        std::vector<std::string> findGroupsByChildName(const std::string& fullName) const;
    };
}

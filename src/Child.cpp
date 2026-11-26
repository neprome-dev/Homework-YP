#include "../include/Child.h"

#include <stdexcept>

namespace miit::kindergarten
{
    Child::Child(const std::string& fullName, const int age, const Gender gender,
                 const std::string& groupName)
        : KindergartenPerson(fullName), age_(age), gender_(gender), groupName_(groupName)
    {
        if (age_ < 2 || age_ > 7)
        {
            throw std::invalid_argument("Возраст ребёнка должен быть от 2 до 7 лет");
        }
        if (groupName_.empty())
        {
            throw std::invalid_argument("Название группы не должно быть пустым");
        }
    }

    int Child::getAge() const noexcept
    {
        return age_;
    }

    Gender Child::getGender() const noexcept
    {
        return gender_;
    }

    const std::string& Child::getGroupName() const noexcept
    {
        return groupName_;
    }

    std::string Child::getDescription() const
    {
        return "Воспитанник: " + getFullName() + ", возраст: " + std::to_string(age_)
               + ", группа: " + groupName_;
    }
}

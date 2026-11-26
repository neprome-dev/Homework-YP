#include "../include/Kindergarten.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace miit::kindergarten
{
    namespace
    {
        /**
         * @brief Сравнить записи по дню и времени начала
         * @param first Первая запись расписания
         * @param second Вторая запись расписания
         * @return true, если первая запись начинается раньше второй
         */
        bool startsBefore(const Activity& first, const Activity& second)
        {
            if (first.getDay() != second.getDay())
            {
                return first.getDay() < second.getDay();
            }
            return first.getStartMinute() < second.getStartMinute();
        }
    }

    bool Kindergarten::hasGroup(const std::string& groupName) const
    {
        return std::find(groupNames_.begin(), groupNames_.end(), groupName) != groupNames_.end();
    }

    bool Kindergarten::hasEducator(const int educatorId) const noexcept
    {
        for (const Educator& educator : educators_)
        {
            if (educator.getId() == educatorId)
            {
                return true;
            }
        }
        return false;
    }

    void Kindergarten::addGroup(const std::string& groupName)
    {
        if (groupName.empty() || hasGroup(groupName))
        {
            throw std::invalid_argument("Название группы пустое или уже занято");
        }
        groupNames_.push_back(groupName);
    }

    void Kindergarten::addChild(const Child& child)
    {
        if (!hasGroup(child.getGroupName()))
        {
            throw std::invalid_argument("Группа воспитанника не зарегистрирована");
        }
        children_.push_back(child);
    }

    void Kindergarten::addEducator(const Educator& educator)
    {
        if (hasEducator(educator.getId()))
        {
            throw std::invalid_argument("Педагог с таким номером уже зарегистрирован");
        }
        educators_.push_back(educator);
    }

    void Kindergarten::addActivity(const Activity& activity)
    {
        if (!hasGroup(activity.getGroupName()))
        {
            throw std::invalid_argument("Группа из расписания не зарегистрирована");
        }
        if (!hasEducator(activity.getEducatorId()))
        {
            throw std::invalid_argument("Педагог из расписания не зарегистрирован");
        }

        for (const Activity& scheduled : activities_)
        {
            const bool sameDay = scheduled.getDay() == activity.getDay();
            const bool timesOverlap = scheduled.getStartMinute() < activity.getEndMinute()
                                      && activity.getStartMinute() < scheduled.getEndMinute();
            if (sameDay && timesOverlap)
            {
                const bool sameGroup = scheduled.getGroupName() == activity.getGroupName();
                const bool sameEducator = scheduled.getEducatorId() == activity.getEducatorId();
                const bool sameRoom = scheduled.getType() == activity.getType()
                                      && activity.getType() != ActivityType::Walk;
                if (sameGroup || sameEducator || sameRoom)
                {
                    throw std::invalid_argument("Группа, педагог или помещение уже заняты в это время");
                }
            }
        }
        activities_.push_back(activity);
    }

    const std::vector<std::string>& Kindergarten::getGroupNames() const noexcept
    {
        return groupNames_;
    }

    const std::vector<Child>& Kindergarten::getChildren() const noexcept
    {
        return children_;
    }

    const std::vector<Educator>& Kindergarten::getEducators() const noexcept
    {
        return educators_;
    }

    std::vector<Child> Kindergarten::getChildrenByGroup(const std::string& groupName) const
    {
        std::vector<Child> result;
        for (const Child& child : children_)
        {
            if (child.getGroupName() == groupName)
            {
                result.push_back(child);
            }
        }
        return result;
    }

    std::vector<Child> Kindergarten::getChildrenByAge(const int age) const
    {
        std::vector<Child> result;
        for (const Child& child : children_)
        {
            if (child.getAge() == age)
            {
                result.push_back(child);
            }
        }
        return result;
    }

    std::vector<Activity> Kindergarten::getEducatorSchedule(const int educatorId) const
    {
        std::vector<Activity> result;
        for (const Activity& activity : activities_)
        {
            if (activity.getEducatorId() == educatorId)
            {
                result.push_back(activity);
            }
        }
        std::sort(result.begin(), result.end(), startsBefore);
        return result;
    }

    std::vector<Activity> Kindergarten::getGroupSchedule(const std::string& groupName,
                                                         const DayOfWeek day) const
    {
        std::vector<Activity> result;
        for (const Activity& activity : activities_)
        {
            if (activity.getGroupName() == groupName && activity.getDay() == day)
            {
                result.push_back(activity);
            }
        }
        std::sort(result.begin(), result.end(), startsBefore);
        return result;
    }

    double Kindergarten::getGenderPercentage(const std::string& groupName, const Gender gender) const
    {
        std::size_t total = 0U;
        std::size_t matching = 0U;
        for (const Child& child : children_)
        {
            if (child.getGroupName() == groupName)
            {
                ++total;
                if (child.getGender() == gender)
                {
                    ++matching;
                }
            }
        }

        if (total == 0U)
        {
            return 0.0;
        }
        return 100.0 * static_cast<double>(matching) / static_cast<double>(total);
    }

    std::vector<std::string> Kindergarten::findGroupsByChildName(const std::string& fullName) const
    {
        std::vector<std::string> result;
        for (const Child& child : children_)
        {
            if (child.getFullName() == fullName)
            {
                const std::string& groupName = child.getGroupName();
                if (std::find(result.begin(), result.end(), groupName) == result.end())
                {
                    result.push_back(groupName);
                }
            }
        }
        return result;
    }
}

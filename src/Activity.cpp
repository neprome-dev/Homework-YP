#include "../include/Activity.h"

#include <stdexcept>

namespace miit::kindergarten
{
    Activity::Activity(const std::string& groupName, const DayOfWeek day, const int startMinute,
                       const int endMinute, const ActivityType type, const int educatorId)
        : groupName_(groupName), day_(day), startMinute_(startMinute), endMinute_(endMinute),
          type_(type), educatorId_(educatorId)
    {
        const int minutesPerDay = 24 * 60;

        if (groupName_.empty())
        {
            throw std::invalid_argument("Название группы не должно быть пустым");
        }
        if (day_ < DayOfWeek::Monday || day_ > DayOfWeek::Sunday)
        {
            throw std::invalid_argument("Неизвестный день недели");
        }
        if (startMinute_ < 0 || endMinute_ > minutesPerDay || startMinute_ >= endMinute_)
        {
            throw std::invalid_argument("Некорректное время начала или окончания");
        }
        if (type_ < ActivityType::Music || type_ > ActivityType::Walk)
        {
            throw std::invalid_argument("Неизвестный вид занятия");
        }
        if (educatorId_ <= 0)
        {
            throw std::invalid_argument("Номер педагога должен быть положительным");
        }
    }

    const std::string& Activity::getGroupName() const noexcept
    {
        return groupName_;
    }

    DayOfWeek Activity::getDay() const noexcept
    {
        return day_;
    }

    int Activity::getStartMinute() const noexcept
    {
        return startMinute_;
    }

    int Activity::getEndMinute() const noexcept
    {
        return endMinute_;
    }

    ActivityType Activity::getType() const noexcept
    {
        return type_;
    }

    int Activity::getEducatorId() const noexcept
    {
        return educatorId_;
    }

    std::string Activity::getPlace() const
    {
        switch (type_)
        {
        case ActivityType::Music:
            return "Музыкальный зал";
        case ActivityType::PhysicalEducation:
            return "Спортивный зал";
        case ActivityType::Drawing:
            return "Кабинет рисования";
        case ActivityType::Walk:
            return "Площадка для прогулок";
        }
        throw std::logic_error("Неизвестный вид занятия");
    }
}

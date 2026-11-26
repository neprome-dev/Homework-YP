#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Activity.h"
#include "../include/Child.h"
#include "../include/Educator.h"
#include "../include/Kindergarten.h"
#include "../include/KindergartenPerson.h"

using namespace miit::kindergarten;

/**
 * @brief Подготовить данные и расписание на рабочую неделю
 * @param firstGroup Название первой группы
 * @param secondGroup Название второй группы
 * @param firstEducator Педагог первой группы
 * @param secondEducator Педагог второй группы
 * @return Детский сад с демонстрационными данными
 */
Kindergarten createKindergarten(
    const std::string& firstGroup,
    const std::string& secondGroup,
    const Educator& firstEducator,
    const Educator& secondEducator);

/**
 * @brief Вывести список детей
 * @param children Дети из результата запроса
 */
void printChildren(const std::vector<Child>& children);

/**
 * @brief Вывести список занятий и прогулок
 * @param schedule Расписание из результата запроса
 */
void printSchedule(const std::vector<Activity>& schedule);

/**
 * @brief Получить название дня недели
 * @param day День недели
 * @return Название дня на русском языке
 */
std::string dayName(const DayOfWeek day);

/**
 * @brief Получить название занятия
 * @param type Вид занятия или прогулка
 * @return Название на русском языке
 */
std::string activityName(const ActivityType type);

/**
 * @brief Вывести время в часах и минутах
 * @param minute Количество минут с начала суток
 */
void printTime(const int minute);

/**
 * @brief Точка входа в программу
 * @return Ноль при успешном выполнении, иначе единица
 */
int main()
{
    try
    {
        const std::string firstGroup = "Солнышко";
        const std::string secondGroup = "Радуга";
        const Educator firstEducator("Петрова Анна Сергеевна", 1);
        const Educator secondEducator("Смирнова Мария Павловна", 2);
        const Kindergarten kindergarten = createKindergarten(
            firstGroup, secondGroup, firstEducator, secondEducator);

        std::cout << "Детский сад\n\nВоспитанники:\n";
        for (const KindergartenPerson& child : kindergarten.getChildren())
        {
            std::cout << child.getDescription() << '\n';
        }

        std::cout << "\nПедагоги:\n";
        for (const KindergartenPerson& educator : kindergarten.getEducators())
        {
            std::cout << educator.getDescription() << '\n';
        }

        std::cout << "\n1. Дети группы «" << firstGroup << "»:\n";
        printChildren(kindergarten.getChildrenByGroup(firstGroup));

        const int age = 7;
        std::cout << "\n2. Дети выбранного возраста (" << age << " лет):\n";
        printChildren(kindergarten.getChildrenByAge(age));

        std::cout << "\n3. Занятость педагога " << firstEducator.getFullName() << ":\n";
        printSchedule(kindergarten.getEducatorSchedule(firstEducator.getId()));

        const DayOfWeek day = DayOfWeek::Friday;
        std::cout << "\n4. Расписание группы «" << secondGroup << "» (" << dayName(day) << "):\n";
        printSchedule(kindergarten.getGroupSchedule(secondGroup, day));

        const double boys = kindergarten.getGenderPercentage(firstGroup, Gender::Boy);
        const double girls = kindergarten.getGenderPercentage(firstGroup, Gender::Girl);
        std::cout << "\n5. Доли в группе «" << firstGroup << "»:\n"
                  << std::fixed << std::setprecision(1)
                  << "Мальчики: " << boys << "%\n"
                  << "Девочки: " << girls << "%\n";

        const std::string fullName = "Иванов Максим Андреевич";
        const std::vector<std::string> groups = kindergarten.findGroupsByChildName(fullName);
        std::cout << "\n6. Поиск группы по ФИО: " << fullName << '\n';
        if (groups.empty())
        {
            std::cout << "Ребёнок не найден.\n";
        }
        for (const std::string& group : groups)
        {
            std::cout << group << '\n';
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

Kindergarten createKindergarten(
    const std::string& firstGroup,
    const std::string& secondGroup,
    const Educator& firstEducator,
    const Educator& secondEducator)
{
    Kindergarten kindergarten;
    kindergarten.addGroup(firstGroup);
    kindergarten.addGroup(secondGroup);
    kindergarten.addEducator(firstEducator);
    kindergarten.addEducator(secondEducator);

    kindergarten.addChild(Child("Иванов Максим Андреевич", 2, Gender::Boy, firstGroup));
    kindergarten.addChild(Child("Орлов Артём Денисович", 3, Gender::Boy, firstGroup));
    kindergarten.addChild(Child("Волкова София Ильинична", 3, Gender::Girl, firstGroup));
    kindergarten.addChild(Child("Иванов Максим Андреевич", 7, Gender::Boy, secondGroup));
    kindergarten.addChild(Child("Соколова Алиса Олеговна", 7, Gender::Girl, secondGroup));

    const int firstEducatorId = firstEducator.getId();
    const int secondEducatorId = secondEducator.getId();
    const std::vector<DayOfWeek> weekdays{
        DayOfWeek::Monday, DayOfWeek::Tuesday, DayOfWeek::Wednesday,
        DayOfWeek::Thursday, DayOfWeek::Friday
    };

    for (const DayOfWeek day : weekdays)
    {
        if (day == DayOfWeek::Monday || day == DayOfWeek::Thursday)
        {
            kindergarten.addActivity(Activity(firstGroup, day, 9 * 60, 9 * 60 + 25,
                                              ActivityType::Music, firstEducatorId));
            kindergarten.addActivity(Activity(secondGroup, day, 9 * 60 + 30, 9 * 60 + 55,
                                              ActivityType::Music, secondEducatorId));
        }

        if (day == DayOfWeek::Tuesday || day == DayOfWeek::Friday)
        {
            kindergarten.addActivity(Activity(firstGroup, day, 9 * 60, 9 * 60 + 25,
                                              ActivityType::PhysicalEducation, firstEducatorId));
            kindergarten.addActivity(Activity(secondGroup, day, 9 * 60 + 30, 9 * 60 + 55,
                                              ActivityType::PhysicalEducation, secondEducatorId));
        }

        kindergarten.addActivity(Activity(firstGroup, day, 10 * 60, 10 * 60 + 45,
                                          ActivityType::Walk, firstEducatorId));
        kindergarten.addActivity(Activity(secondGroup, day, 10 * 60, 10 * 60 + 45,
                                          ActivityType::Walk, secondEducatorId));

        if (day == DayOfWeek::Wednesday || day == DayOfWeek::Friday)
        {
            kindergarten.addActivity(Activity(firstGroup, day, 11 * 60, 11 * 60 + 25,
                                              ActivityType::Drawing, firstEducatorId));
            kindergarten.addActivity(Activity(secondGroup, day, 11 * 60 + 30, 11 * 60 + 55,
                                              ActivityType::Drawing, secondEducatorId));
        }

        kindergarten.addActivity(Activity(firstGroup, day, 16 * 60, 16 * 60 + 45,
                                          ActivityType::Walk, firstEducatorId));
        kindergarten.addActivity(Activity(secondGroup, day, 16 * 60, 16 * 60 + 45,
                                          ActivityType::Walk, secondEducatorId));
    }

    return kindergarten;
}

void printChildren(const std::vector<Child>& children)
{
    if (children.empty())
    {
        std::cout << "Дети не найдены.\n";
    }
    for (const Child& child : children)
    {
        std::cout << child.getDescription() << '\n';
    }
}

void printSchedule(const std::vector<Activity>& schedule)
{
    if (schedule.empty())
    {
        std::cout << "Занятий и прогулок нет.\n";
    }
    for (const Activity& activity : schedule)
    {
        std::cout << dayName(activity.getDay()) << ", ";
        printTime(activity.getStartMinute());
        std::cout << "–";
        printTime(activity.getEndMinute());
        std::cout << " — " << activityName(activity.getType())
                  << ", группа «" << activity.getGroupName() << "», "
                  << activity.getPlace() << '\n';
    }
}

std::string dayName(const DayOfWeek day)
{
    switch (day)
    {
    case DayOfWeek::Monday:
        return "Понедельник";
    case DayOfWeek::Tuesday:
        return "Вторник";
    case DayOfWeek::Wednesday:
        return "Среда";
    case DayOfWeek::Thursday:
        return "Четверг";
    case DayOfWeek::Friday:
        return "Пятница";
    case DayOfWeek::Saturday:
        return "Суббота";
    case DayOfWeek::Sunday:
        return "Воскресенье";
    }

    return "Неизвестный день";
}

std::string activityName(const ActivityType type)
{
    switch (type)
    {
    case ActivityType::Music:
        return "Музыка";
    case ActivityType::PhysicalEducation:
        return "Физкультура";
    case ActivityType::Drawing:
        return "Рисование";
    case ActivityType::Walk:
        return "Прогулка";
    }

    return "Неизвестное занятие";
}

void printTime(const int minute)
{
    std::cout << std::setfill('0') << std::setw(2) << minute / 60
              << ':' << std::setw(2) << minute % 60 << std::setfill(' ');
}

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "Activity.h"
#include "Child.h"
#include "Educator.h"
#include "Kindergarten.h"
#include "KindergartenPerson.h"

using namespace miit::kindergarten;

namespace
{
    /**
     * @brief Создать детский сад с группами и педагогами для тестов
     * @return Детский сад без воспитанников и записей расписания
     */
    Kindergarten makeKindergarten()
    {
        Kindergarten kindergarten;
        kindergarten.addGroup("Звёздочки");
        kindergarten.addGroup("Солнышко");
        kindergarten.addGroup("Ромашки");
        kindergarten.addEducator(Educator("Соколова Анна Игоревна", 1));
        kindergarten.addEducator(Educator("Орлов Михаил Иванович", 2));
        return kindergarten;
    }
}

TEST(KindergartenPerson, ProvidesDescriptionsThroughBaseType)
{
    const Child child("Иванов Пётр Сергеевич", 2, Gender::Boy, "Звёздочки");
    const Educator educator("Соколова Анна Игоревна", 1);
    const KindergartenPerson& childPerson = child;
    const KindergartenPerson& educatorPerson = educator;

    EXPECT_NE(childPerson.getDescription().find(child.getFullName()), std::string::npos);
    EXPECT_NE(educatorPerson.getDescription().find(educator.getFullName()), std::string::npos);
}

TEST(Child, AcceptsBothAgeLimits)
{
    const Child youngest("Иванов Пётр Сергеевич", 2, Gender::Boy, "Звёздочки");
    const Child oldest("Волкова Анна Олеговна", 7, Gender::Girl, "Солнышко");

    EXPECT_EQ(youngest.getAge(), 2);
    EXPECT_EQ(oldest.getAge(), 7);
}

TEST(Kindergarten, FiltersChildrenByGroupAndAge)
{
    Kindergarten kindergarten = makeKindergarten();
    kindergarten.addChild(Child("Иванов Пётр Сергеевич", 5, Gender::Boy, "Звёздочки"));
    kindergarten.addChild(Child("Волкова Анна Олеговна", 7, Gender::Girl, "Звёздочки"));
    kindergarten.addChild(Child("Петрова Мария Игоревна", 5, Gender::Girl, "Солнышко"));
    const Kindergarten& view = kindergarten;

    const std::vector<Child> group = view.getChildrenByGroup("Звёздочки");
    ASSERT_EQ(group.size(), 2U);
    EXPECT_EQ(group[0].getGroupName(), "Звёздочки");
    EXPECT_EQ(group[1].getGroupName(), "Звёздочки");

    const std::vector<Child> childrenAgedFive = view.getChildrenByAge(5);
    ASSERT_EQ(childrenAgedFive.size(), 2U);
    EXPECT_EQ(childrenAgedFive[0].getAge(), 5);
    EXPECT_EQ(childrenAgedFive[1].getAge(), 5);
    EXPECT_TRUE(view.getChildrenByGroup("Ромашки").empty());
    EXPECT_TRUE(view.getChildrenByAge(4).empty());
}

TEST(Kindergarten, CalculatesPercentagesWithinSelectedGroup)
{
    Kindergarten kindergarten = makeKindergarten();
    kindergarten.addChild(Child("Иванов Пётр Сергеевич", 5, Gender::Boy, "Звёздочки"));
    kindergarten.addChild(Child("Волкова Анна Олеговна", 5, Gender::Girl, "Звёздочки"));
    kindergarten.addChild(Child("Петрова Мария Игоревна", 5, Gender::Girl, "Звёздочки"));
    kindergarten.addChild(Child("Попов Илья Олегович", 5, Gender::Boy, "Солнышко"));

    EXPECT_NEAR(kindergarten.getGenderPercentage("Звёздочки", Gender::Boy), 100.0 / 3.0, 1.0e-9);
    EXPECT_NEAR(kindergarten.getGenderPercentage("Звёздочки", Gender::Girl), 200.0 / 3.0, 1.0e-9);
    EXPECT_DOUBLE_EQ(kindergarten.getGenderPercentage("Ромашки", Gender::Girl), 0.0);
    EXPECT_DOUBLE_EQ(kindergarten.getGenderPercentage("Солнышко", Gender::Boy), 100.0);
}

TEST(Kindergarten, FindsDistinctGroupsByExactFullName)
{
    Kindergarten kindergarten = makeKindergarten();
    const std::string fullName = "Иванов Пётр Сергеевич";
    kindergarten.addChild(Child(fullName, 5, Gender::Boy, "Звёздочки"));
    kindergarten.addChild(Child(fullName, 6, Gender::Boy, "Звёздочки"));
    kindergarten.addChild(Child(fullName, 7, Gender::Boy, "Солнышко"));
    kindergarten.addChild(Child("Иванов Пётр Ильич", 5, Gender::Boy, "Ромашки"));

    const std::vector<std::string> groups = kindergarten.findGroupsByChildName(fullName);
    ASSERT_EQ(groups.size(), 2U);
    EXPECT_NE(std::find(groups.begin(), groups.end(), "Звёздочки"), groups.end());
    EXPECT_NE(std::find(groups.begin(), groups.end(), "Солнышко"), groups.end());
    EXPECT_TRUE(kindergarten.findGroupsByChildName("Иванов Пётр").empty());
}

TEST(Kindergarten, ReturnsGroupScheduleForSelectedDayInTimeOrder)
{
    Kindergarten kindergarten = makeKindergarten();
    kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 620, 640, ActivityType::Drawing, 1));
    kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 540, 560, ActivityType::Music, 1));
    kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Tuesday, 540, 560, ActivityType::Music, 1));
    kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Monday, 540, 560, ActivityType::PhysicalEducation, 2));

    const std::vector<Activity> schedule = kindergarten.getGroupSchedule("Звёздочки", DayOfWeek::Monday);
    ASSERT_EQ(schedule.size(), 2U);
    EXPECT_EQ(schedule[0].getStartMinute(), 540);
    EXPECT_EQ(schedule[0].getEndMinute(), 560);
    EXPECT_EQ(schedule[1].getStartMinute(), 620);
    EXPECT_EQ(schedule[1].getGroupName(), "Звёздочки");
    EXPECT_EQ(schedule[1].getDay(), DayOfWeek::Monday);
    EXPECT_TRUE(kindergarten.getGroupSchedule("Звёздочки", DayOfWeek::Sunday).empty());
}

TEST(Kindergarten, ReturnsEducatorScheduleAcrossDaysAndGroups)
{
    Kindergarten kindergarten = makeKindergarten();
    kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Friday, 540, 560, ActivityType::Music, 1));
    kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Monday, 620, 640, ActivityType::Walk, 1));
    kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 540, 560, ActivityType::Music, 1));
    kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Monday, 540, 560, ActivityType::Drawing, 2));

    const std::vector<Activity> schedule = kindergarten.getEducatorSchedule(1);
    ASSERT_EQ(schedule.size(), 3U);
    EXPECT_EQ(schedule[0].getGroupName(), "Звёздочки");
    EXPECT_EQ(schedule[1].getType(), ActivityType::Walk);
    EXPECT_EQ(schedule[2].getDay(), DayOfWeek::Friday);
    EXPECT_EQ(schedule[2].getEducatorId(), 1);
    EXPECT_TRUE(kindergarten.getEducatorSchedule(100).empty());
}

TEST(Activity, UsesDifferentPlacesForDifferentActivities)
{
    const Activity music("Звёздочки", DayOfWeek::Monday, 540, 560, ActivityType::Music, 1);
    const Activity physicalEducation("Звёздочки", DayOfWeek::Monday, 560, 580, ActivityType::PhysicalEducation, 1);
    const Activity drawing("Звёздочки", DayOfWeek::Monday, 580, 600, ActivityType::Drawing, 1);
    const Activity walk("Звёздочки", DayOfWeek::Monday, 600, 620, ActivityType::Walk, 1);

    const std::string musicPlace{music.getPlace()};
    const std::string physicalEducationPlace{physicalEducation.getPlace()};
    const std::string drawingPlace{drawing.getPlace()};
    const std::string walkPlace{walk.getPlace()};

    EXPECT_FALSE(musicPlace.empty());
    EXPECT_FALSE(physicalEducationPlace.empty());
    EXPECT_FALSE(drawingPlace.empty());
    EXPECT_FALSE(walkPlace.empty());
    EXPECT_NE(musicPlace, physicalEducationPlace);
    EXPECT_NE(musicPlace, drawingPlace);
    EXPECT_NE(physicalEducationPlace, drawingPlace);
    EXPECT_NE(walkPlace, musicPlace);
    EXPECT_NE(walkPlace, physicalEducationPlace);
    EXPECT_NE(walkPlace, drawingPlace);
}

TEST(Kindergarten, RejectsInvalidGroupsChildrenAndEducators)
{
    Kindergarten kindergarten = makeKindergarten();

    EXPECT_THROW(kindergarten.addGroup(""), std::invalid_argument);
    EXPECT_THROW(kindergarten.addGroup("Звёздочки"), std::invalid_argument);
    EXPECT_THROW(kindergarten.addChild(Child("Иванов Пётр Сергеевич", 1, Gender::Boy, "Звёздочки")),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addChild(Child("Иванов Пётр Сергеевич", 8, Gender::Boy, "Звёздочки")),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addChild(Child("Иванов Пётр Сергеевич", 5, Gender::Boy, "Неизвестная")),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addEducator(Educator("Петрова Ольга Сергеевна", 0)), std::invalid_argument);
    EXPECT_THROW(kindergarten.addEducator(Educator("Петрова Ольга Сергеевна", 1)), std::invalid_argument);

    EXPECT_TRUE(kindergarten.getChildren().empty());
    EXPECT_EQ(kindergarten.getEducators().size(), 2U);
}

TEST(Kindergarten, RejectsInvalidActivityTimesAndUnknownParticipants)
{
    Kindergarten kindergarten = makeKindergarten();

    EXPECT_THROW(kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, -1, 560, ActivityType::Music, 1)),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 560, 540, ActivityType::Music, 1)),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 540, 540, ActivityType::Music, 1)),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 540, 1441, ActivityType::Music, 1)),
        std::invalid_argument);
    const Activity unknownGroup("Неизвестная", DayOfWeek::Monday, 540, 560, ActivityType::Music, 1);
    const Activity unknownEducator("Звёздочки", DayOfWeek::Monday, 540, 560, ActivityType::Music, 100);
    EXPECT_THROW(kindergarten.addActivity(unknownGroup), std::invalid_argument);
    EXPECT_THROW(kindergarten.addActivity(unknownEducator), std::invalid_argument);

    EXPECT_TRUE(kindergarten.getGroupSchedule("Звёздочки", DayOfWeek::Monday).empty());
}

TEST(Kindergarten, RejectsOverlappingBookingsOfGroupEducatorOrRoom)
{
    Kindergarten kindergarten = makeKindergarten();
    kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 540, 560, ActivityType::Music, 1));

    const Activity sameGroup("Звёздочки", DayOfWeek::Monday, 550, 570, ActivityType::PhysicalEducation, 2);
    EXPECT_THROW(kindergarten.addActivity(sameGroup), std::invalid_argument);
    EXPECT_THROW(kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Monday, 550, 570, ActivityType::Drawing, 1)),
        std::invalid_argument);
    EXPECT_THROW(kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Monday, 550, 570, ActivityType::Music, 2)),
        std::invalid_argument);

    const Activity nextActivity("Звёздочки", DayOfWeek::Monday, 560, 580, ActivityType::Music, 1);
    EXPECT_NO_THROW(kindergarten.addActivity(nextActivity));
    EXPECT_EQ(kindergarten.getGroupSchedule("Звёздочки", DayOfWeek::Monday).size(), 2U);
    EXPECT_TRUE(kindergarten.getGroupSchedule("Солнышко", DayOfWeek::Monday).empty());
}

TEST(Kindergarten, AllowsParallelWalksForDifferentGroupsAndEducators)
{
    Kindergarten kindergarten = makeKindergarten();
    kindergarten.addActivity(Activity("Звёздочки", DayOfWeek::Monday, 600, 630, ActivityType::Walk, 1));

    EXPECT_NO_THROW(kindergarten.addActivity(Activity("Солнышко", DayOfWeek::Monday, 600, 630, ActivityType::Walk, 2)));
    EXPECT_THROW(kindergarten.addActivity(Activity("Ромашки", DayOfWeek::Monday, 610, 640, ActivityType::Walk, 1)),
        std::invalid_argument);
    EXPECT_EQ(kindergarten.getGroupSchedule("Солнышко", DayOfWeek::Monday).size(), 1U);
}

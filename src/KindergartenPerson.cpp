#include "../include/KindergartenPerson.h"

#include <stdexcept>

namespace miit::kindergarten
{
    KindergartenPerson::KindergartenPerson(const std::string& fullName)
        : fullName_(fullName)
    {
        if (fullName_.empty())
        {
            throw std::invalid_argument("ФИО не должно быть пустым");
        }
    }

    KindergartenPerson::~KindergartenPerson() = default;

    const std::string& KindergartenPerson::getFullName() const noexcept
    {
        return fullName_;
    }
}

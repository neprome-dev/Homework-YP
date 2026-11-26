#include "../include/Educator.h"

#include <stdexcept>

namespace miit::kindergarten
{
    Educator::Educator(const std::string& fullName, const int id)
        : KindergartenPerson(fullName), id_(id)
    {
        if (id_ <= 0)
        {
            throw std::invalid_argument("Номер педагога должен быть положительным");
        }
    }

    int Educator::getId() const noexcept
    {
        return id_;
    }

    std::string Educator::getDescription() const
    {
        return "Педагог: " + getFullName() + ", номер: " + std::to_string(id_);
    }
}

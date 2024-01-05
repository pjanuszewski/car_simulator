#include "GearBox.h"
#include <stdexcept>

GearBox::GearBox() : gear(std::make_shared<unsigned int>(0)) {}

unsigned int GearBox::get_gear() const
{
    return *gear;
}


void GearBox::set_gear(const int& new_gear)
{
    if (new_gear < 1 || new_gear > 5) {
        throw std::invalid_argument("Invalid gear number");
    }
    *gear = new_gear;
}

std::shared_ptr<unsigned int> GearBox::get_gear_ptr() const
{
    return gear;
}
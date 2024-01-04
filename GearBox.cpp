#include "GearBox.h"

GearBox::GearBox() : gear(std::make_shared<unsigned int>(1)) {}

unsigned int GearBox::get_gear() const
{
    return *gear;
}

void GearBox::set_gear(unsigned int new_gear)
{
    *gear = new_gear;
}

std::shared_ptr<unsigned int> GearBox::get_gear_ptr() const
{
    return gear;
}
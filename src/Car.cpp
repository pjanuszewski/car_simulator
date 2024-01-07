#include "Car.h"

Car::Car() : position(std::make_unique<std::vector<double>>(1, 0.0)),
    speed(std::make_unique<std::vector<double>>(1, 0.0)), 
    acceleration(std::make_unique<std::vector<double>>(1, 0.0))
{
    // Make sure to fully construct the Car object before calling shared_from_this()
    //engine = std::make_shared<Engine>(shared_from_this(), gearBox->get_gear_ptr(), driver->get_gas_pedal_ptr(), driver->get_brake_pedal_ptr());
}
double Car::get_position() const
{
    return position->back();
}

double Car::get_speed() const
{
    return speed->back();
}

double Car::get_acceleration() const
{
    return acceleration->back();
}

void Car::set_position(const unsigned int& time)
{
    position->emplace_back(get_position() + this->get_speed() * time*0.001);
}

void Car::set_speed(const double& new_speed)
{
    speed->emplace_back(new_speed);
}

void Car::set_acceleration(const unsigned int& time)
{
    if (speed->size() >= 2)
    {
        double last_speed = speed->back();
        double second_to_last_speed = speed->at(speed->size() - 2);
        double new_acceleration = (last_speed - second_to_last_speed) / ((0.001)*time);
        acceleration->emplace_back(new_acceleration);
    }
}
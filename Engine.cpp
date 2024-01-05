#include "Engine.h"
#include "Car.h"
#include "Driver.h"
#include "GearBox.h"
#include <algorithm>
#include <cstddef>
#include <memory>

Engine::Engine( const std::shared_ptr<Car>& car,
                const std::shared_ptr<GearBox>& gear,
                const std::shared_ptr<Driver>& driver) :
    car1(car),
    gear1(gear),
    driver1(driver)
{}

double Engine::new_speed()
{
    double new_speed = (car1->get_speed()+gear1->get_gear()*driver1->get_gas_pedal()-drag*car1->get_speed()-driver1->get_brake_pedal()*0.8);
    new_speed = std::clamp(new_speed, 0.0, max_speed);
    return new_speed;
}

double Engine::get_rpm() const
{
    double speed_mph = car1->get_speed() * 2.23694; // Convert speed from m/s to mph
    double gear_ratio = gear1->get_gear();
    double tire_diameter_in = 70 * 0.393701; // Convert tire diameter from cm to inches

    return (speed_mph * gear_ratio * 336) / tire_diameter_in;
}
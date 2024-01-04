#include "Engine.h"
#include "Car.h"
#include "Driver.h"
#include "GearBox.h"
#include <cstddef>
#include <memory>

Engine::Engine( const std::shared_ptr<Car>& car,
                const std::shared_ptr<GearBox>& gear,
                const std::shared_ptr<Driver>& driver) :
    car1(car),
    gear1(gear),
    driver1(driver)
{}

std::unique_ptr<double> Engine::new_speed()
{
    std::unique_ptr<double> new_speed_ptr = std::make_unique<double>(car1->get_speed() 
    + gear1->get_gear() * 
    *driver1->get_gas_pedal_ptr() 
    - drag * car1->get_speed());
    return new_speed_ptr;
}
#ifndef ENGINE_H
#define ENGINE_H

#include "Driver.h"
#include "GearBox.h"
#include <memory>
#include <algorithm>
class Car;

class Engine
{
public:
    Engine( const std::shared_ptr<Car>& car,
            const std::shared_ptr<GearBox>& gear,
            const std::shared_ptr<Driver>& driver);

    double new_speed();
    bool turn_on_engine();
    bool turn_off_engine();
    bool get_engine_state() const;
    double get_rpm() const;

private:
    std::shared_ptr<Car> car1;
    std::shared_ptr<GearBox> gear1;
    std::shared_ptr<Driver> driver1;
    static bool engine_state;
    const double drag = 0.957;
    double max_speed = 300.0;
};

#endif // ENGINE_H
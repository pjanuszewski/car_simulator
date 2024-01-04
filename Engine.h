#ifndef ENGINE_H
#define ENGINE_H

#include "Driver.h"
#include "GearBox.h"
#include <memory>
class Car;

class Engine
{
public:
    Engine( const std::shared_ptr<Car>& car,
            const std::shared_ptr<GearBox>& gear,
            const std::shared_ptr<Driver>& driver);

    std::unique_ptr<double> new_speed();
    bool turn_on_engine();
    bool turn_off_engine();
    bool get_engine_state() const;
    double get_rpm() const;

private:
    std::shared_ptr<Car> car1;
    std::shared_ptr<GearBox> gear1;
    std::shared_ptr<Driver> driver1;
    std::unique_ptr<double> new_speed_ptr;
    static bool engine_state;
    double drag = 0.3;
};

#endif // ENGINE_H
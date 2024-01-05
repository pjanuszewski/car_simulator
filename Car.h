#ifndef CAR_H
#define CAR_H

#include <memory>
#include <vector>
#include <list>
#include <array>
#include "Driver.h"
#include "Engine.h"
#include "GearBox.h"

class Car
{
public:
    Car();
    double get_position() const;
    double get_speed() const;
    double get_acceleration() const;
    void set_position(const unsigned int& time);
    void set_speed(const double& new_speed);
    void set_acceleration(const unsigned int& time);
    double get_kinematics() const;
    void update_speed();

private:
    std::shared_ptr<std::vector<double>> position;
    std::shared_ptr<std::vector<double>> speed;
    std::shared_ptr<std::vector<double>> acceleration;
};

#endif // CAR_H
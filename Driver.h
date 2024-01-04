#ifndef DRIVER_H
#define DRIVER_H

#include <memory>
#include <chrono>
#include <termios.h>
#include <unistd.h>

class Driver
{
public:
    Driver();
    void checkGasPedal();
    void checkBrakePedal();
    std::shared_ptr<double> get_gas_pedal_ptr() const;
    std::shared_ptr<double> get_brake_pedal_ptr() const;
    void decrement_gas_pedal();
    void decrement_brake_pedal();
    void increment_gas_pedal();
    void increment_brake_pedal();

private:
    std::shared_ptr<double> gas_pedal;
    std::shared_ptr<double> brake_pedal;
};

#endif // DRIVER_H
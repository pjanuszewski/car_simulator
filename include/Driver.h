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
    double get_gas_pedal() const;
    double get_brake_pedal() const;
    void zero_gas_pedal();
    void zero_brake_pedal();
    void increment_gas_pedal();
    void increment_brake_pedal();

private:
    double gas_pedal;
    double brake_pedal;
};

#endif // DRIVER_H
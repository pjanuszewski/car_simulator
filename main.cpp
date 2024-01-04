#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include "Driver.h"
#include "Engine.h"
#include "GearBox.h"
#include "Car.h"

class Simulation
{
public:
    Simulation() : 
    car(std::make_shared<Car>()),
    driver(std::make_shared<Driver>()),
    gearBox(std::make_shared<GearBox>()),
    engine(std::make_shared<Engine>(car, gearBox, driver)),
    sim_state(true) {}
    void display_kinematics() const
    {
        std::ofstream file("output.txt", std::ios::trunc);
        while(sim_state)
        {
            file << "Position: " << car->get_position() << "\t Speed: "<< car->get_speed() << "\t Acceleration: " << car->get_acceleration() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(time_step));
            engine->new_speed();
        }
    }
    bool get_sim_state() const
    {
        return sim_state;
    }
    Driver get_driver() const
    {
        return *driver;
    }
private:
    std::shared_ptr<Driver> driver;
    std::shared_ptr<Car> car;
    std::shared_ptr<GearBox> gearBox;
    std::shared_ptr<Engine> engine;
    std::string input;
    bool sim_state;
    unsigned int time_step = 200;
};

int main() {
    
    Simulation sim;
    std::thread displayThread;
    std::thread gas_pedal_thread;
    std::thread brake_pedal_thread;

    while (sim.get_sim_state())
    {
        displayThread = std::thread([&sim]() {
            sim.display_kinematics();
        });

        gas_pedal_thread = std::thread([&sim]() {
            sim.get_driver().checkGasPedal();
        });

        brake_pedal_thread = std::thread([&sim]() {
            sim.get_driver().checkBrakePedal();
        });

        displayThread.join();
        gas_pedal_thread.join();
        brake_pedal_thread.join();
    }

    displayThread.join();
    gas_pedal_thread.join();
    brake_pedal_thread.join();

    return 0;
}
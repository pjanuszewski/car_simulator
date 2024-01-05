#include <SFML/Window/Cursor.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include "Driver.h"
#include "Engine.h"
#include "GearBox.h"
#include "Car.h"
#include <iomanip>
#include <algorithm>


class Simulation
{
public:
    Simulation() : 
    car(std::make_shared<Car>()),
    driver(std::make_shared<Driver>()),
    gearBox(std::make_shared<GearBox>()),
    engine(std::make_shared<Engine>(car, gearBox, driver)),
    sim_state(true),
    input() {}

    bool get_sim_state() const
    {
        return sim_state;
    }
    void set_sim_state()
    {
        sim_state = false;
    }
    Driver& get_driver() const
    {
        return *driver;
    }
    GearBox& get_gearBox() const
    {
        return *gearBox;
    }
    Engine& get_engine() const
    {
        return *engine;
    }
    void display_kinematics() const
    {
        std::ofstream file("output.txt", std::ios::trunc);

        while(sim_state)
        {
            int space = 8;
            file << std::fixed << std::setprecision(2)
                << "Position: "     << std::right << std::setw(space) << car->get_position()     << " | "
                << "Speed: "        << std::right << std::setw(space) << car->get_speed()        << " | "
                << "Acceleration: " << std::right << std::setw(space) << car->get_acceleration() << " | "
                << "RPM: "          << std::right << std::setw(space) << engine->get_rpm()       << " | "
                << "Gear: "         << std::right << std::setw(3)     << gearBox->get_gear()     << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(time_step));

            car->set_speed(engine->new_speed());
            car->set_position(time_step);
            car->set_acceleration(time_step);
        }

    file.close();
}
    std::string input;
private:
    std::shared_ptr<Driver> driver;
    std::shared_ptr<Car> car;
    std::shared_ptr<GearBox> gearBox;
    std::shared_ptr<Engine> engine;
    bool sim_state;
    unsigned int time_step = 500;
};


int main() {
    Simulation sim;
    std::string input;
    // Start the simulation in a separate thread
    std::cout << "Turn on the engine by pressing e" << std::endl;
    while (input != "e") {
        std::cin >> input;
    }
    std::thread sim_thread;
    try 
    {
        sim_thread = std::thread([&sim]() {
            sim.display_kinematics();
        });
    }
    catch(const std::system_error& e) 
    {
        std::cout << e.what() << std::endl;
    }

    while (sim.get_sim_state()) 
    {
        std::cin >> sim.input;
        if (sim.input == "q") {
            sim.set_sim_state();
        } else if (sim.input == "g") {
            sim.get_driver().increment_gas_pedal();
        } else if (sim.input == "b") {
            sim.get_driver().increment_brake_pedal();
        } else if (sim.input == "1") {
            sim.get_gearBox().set_gear(1);
        } else if (sim.input == "2") {
            sim.get_gearBox().set_gear(2);
        } else if (sim.input == "3") {
            sim.get_gearBox().set_gear(3);
        } else if (sim.input == "4") {
            sim.get_gearBox().set_gear(4);
        } else if (sim.input == "5") {
            sim.get_gearBox().set_gear(5);
        } else {
            sim.get_driver().zero_brake_pedal();
            sim.get_driver().zero_gas_pedal();
        }
    }
        sim_thread.join();
    return 0;
}
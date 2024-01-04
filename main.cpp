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
            file << std::fixed << std::setprecision(3)
                << "Position: " << std::right << std::setw(7) << car->get_position() << "    "
                << "Speed: " << std::right << std::setw(7) << car->get_speed() << "    "
                << "Acceleration: " << std::right << std::setw(7) << car->get_acceleration() << "    "
                << "RPM: " << std::right << std::setw(7) << engine->get_rpm() << "    "
                << "Gear: " << std::right << std::setw(7) << gearBox->get_gear() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(time_step));
            car->set_speed(*engine->new_speed());
            car->set_position(time_step);
            car->set_acceleration(time_step);
        }
        file.close();
    }
    void handle_user_input(Simulation& sim) 
    {
    while (sim.get_sim_state()) {
        std::cin >> sim.input;
        if (sim.input == "q") {
            sim.set_sim_state();
        } else if (sim.input == "g") {
            sim.get_driver().increment_gas_pedal();
        } else if (sim.input == "b") {
            sim.get_driver().increment_brake_pedal();
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
    std::thread sim_thread([&sim]() {
        sim.display_kinematics();
    });

    std::cin >> input;

    while (sim.get_sim_state()) {
        if (input == "q") {
            sim.set_sim_state();
        } else if (input == "g") {
            sim.get_driver().increment_gas_pedal();
        } else if (input == "b") {
            sim.get_driver().increment_brake_pedal();
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
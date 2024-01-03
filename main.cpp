#include <SFML/Graphics/Font.hpp>
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <chrono>
#include <list>
#include <atomic>
#include <vector>
#include <cmath>
#include <termios.h>
#include <unistd.h>

class Car 
{
public:
    Car() : position(std::make_unique<std::vector<double>>()), speed(std::make_unique<std::vector<double>>()), acceleration(std::make_unique<std::list<double>>()) {}
    
    double get_position() const
    {
        return position->back();
    }
    double get_speed() const
    {
        return speed->back();
    }
    double get_acceleration() const
    {
        return acceleration->back();
    }
    void set_position(double& new_position)
    {
        position->emplace_back(new_position);
    }
    void set_speed(double& new_speed)
    {
        speed->emplace_back(new_speed);
    }
    void set_acceleration(double& new_acceleration)
    {
        acceleration->emplace_back(new_acceleration);
    }

    double get_kinematics() const
    {
        return (*kinematics)[get_position(), get_speed(), get_acceleration()];
    }

private:
    std::unique_ptr<std::vector<double>> position;
    std::unique_ptr<std::vector<double>> speed;
    std::unique_ptr<std::list<double>> acceleration;
    std::unique_ptr<std::array<double, 3>> kinematics;
};

class GearBox : public Car
{
public:
    GearBox() : gear(std::make_shared<unsigned int>()) {}

    unsigned int get_gear() const
    {
        return *gear;
    }

    void set_gear(unsigned int new_gear)
    {
        *gear = new_gear;
    }

private:
    std::shared_ptr<unsigned int> gear;
};

class Driver
{
public:
    void checkGasPedal() {
        char ch;
        std::chrono::steady_clock::time_point keyPressTime;
        bool isKeyPressed = false;
        double max_gas_pedal_value = 100.0; // Set your maximum value

        // Set terminal to raw mode
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        termios term_orig = term; // Save original settings
        term.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        while (true) {
            if (read(STDIN_FILENO, &ch, 1) < 0) {
                // Error reading from stdin
                break;
            }

            if (ch == 'f') 
            {
                if (!isKeyPressed) 
                {
                    keyPressTime = std::chrono::steady_clock::now();
                    isKeyPressed = true;
                }
            } 
            else if (isKeyPressed) 
            {
                auto keyReleaseTime = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(keyReleaseTime - keyPressTime).count();
                *gas_pedal += duration; // Increase gas_pedal value relative to duration
                if (*gas_pedal > max_gas_pedal_value) 
                {
                    *gas_pedal = max_gas_pedal_value; // Limit gas_pedal to maximum value
                }
                isKeyPressed = false;
            }
            else if (!isKeyPressed) 
            {
                *gas_pedal = 0.0; // Reset gas_pedal value
            }
        }

        // Restore original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
    }

    void checkBrakePedal() {
        char ch;
        std::chrono::steady_clock::time_point keyPressTime;
        bool isKeyPressed = false;
        double max_brake_pedal_value = 100.0; // Set your maximum value

        // Set terminal to raw mode
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        termios term_orig = term; // Save original settings
        term.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        while (true) {
            if (read(STDIN_FILENO, &ch, 1) < 0) {
                // Error reading from stdin
                break;
            }

            if (ch == 's') 
            {
                if (!isKeyPressed) 
                {
                    keyPressTime = std::chrono::steady_clock::now();
                    isKeyPressed = true;
                }
            } 
            else if (isKeyPressed) 
            {
                auto keyReleaseTime = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(keyReleaseTime - keyPressTime).count();
                *brake_pedal += duration; // Increase brake_pedal value relative to duration
                if (*brake_pedal > max_brake_pedal_value) 
                {
                    *brake_pedal = max_brake_pedal_value; // Limit brake_pedal to maximum value
                }
                isKeyPressed = false;
            }
            else if (!isKeyPressed) 
            {
                *brake_pedal = 0.0; // Reset brake_pedal value
            }
        }

        // Restore original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
    }
private:
    std::shared_ptr<double> gas_pedal;
    std::shared_ptr<double> brake_pedal;
};

class Engine : public Car
{
public:
    Engine() : gear(std::make_shared<unsigned int>()), gas_pedal(std::make_shared<double>()), brake_pedal(std::make_shared<double>()) {}
    Engine(const std::shared_ptr<unsigned int>& gear, const std::shared_ptr<double>& gas_pedal, const std::shared_ptr<double>& brake_pedal) : gear(gear), gas_pedal(gas_pedal), brake_pedal(brake_pedal) {}
    void new_speed()
    {
        double new_speed = get_speed() + *gas_pedal * *gear - *brake_pedal - drag;
        set_speed(new_speed);
    }
private:
    std::shared_ptr<unsigned int> gear;
    std::shared_ptr<double> gas_pedal;
    std::shared_ptr<double> brake_pedal;
    double drag = 0.1;
};

class Simulation : Car, public Driver
{
public:
    Simulation() : car(std::make_unique<Car>()), engine(std::make_unique<Engine>()), driver(std::make_unique<Driver>()), sim_state(true) {}
    void display_kinematics() const
    {
        std::ofstream file("output.txt", std::ios::trunc);
        while(sim_state)
        {
            file << "Position: " << car->get_position() << '\t' << car->get_speed() << '\t' << car->get_acceleration() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(time_step));
            engine->new_speed();
        }
    }
    bool get_sim_state() const
    {
        return sim_state;
    }
private:
    std::unique_ptr<Car> car;
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Driver> driver;
    bool sim_state;
    unsigned int time_step = 200;
};

int main() {
    
    Simulation sim;
    sf::Font font;
    if (!font.loadFromFile("/home/pawelj/Git_repos/car_simulator/build/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    std::thread displayThread;
    std::thread gas_pedal_thread;
    std::thread brake_pedal_thread;

    while (sim.get_sim_state())
    {
        displayThread = std::thread([&sim]() {
            sim.display_kinematics();
        });

        gas_pedal_thread = std::thread([&sim]() {
            sim.checkGasPedal();
        });

        brake_pedal_thread = std::thread([&sim]() {
            sim.checkBrakePedal();
        });
    }

    displayThread.join();
    gas_pedal_thread.join();
    brake_pedal_thread.join();

    return 0;
}
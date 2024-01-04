#include "Driver.h"
#include <memory>

Driver::Driver() : gas_pedal(std::make_shared<double>(0.0)),
brake_pedal(std::make_shared<double>(0.0)) {}

void Driver::checkGasPedal() {
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

    void Driver::checkBrakePedal() {
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

            if (ch == 'b') 
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

void Driver::increment_gas_pedal() {
    *gas_pedal += 5.0;
}

void Driver::increment_brake_pedal() {
    *brake_pedal += 10.0;
}

void Driver::decrement_gas_pedal() {
    *gas_pedal -= 10.0;
}

std::shared_ptr<double> Driver::get_gas_pedal_ptr() const {
    return gas_pedal;
}

std::shared_ptr<double> Driver::get_brake_pedal_ptr() const {
    return brake_pedal;
}
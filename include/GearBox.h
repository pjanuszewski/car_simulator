#ifndef GEARBOX_H
#define GEARBOX_H

#include <memory>

class GearBox
{
public:
    GearBox();

    unsigned int get_gear() const;
    void set_gear(const int& new_gear);
    std::shared_ptr<unsigned int> get_gear_ptr() const;

private:
    std::shared_ptr<unsigned int> gear;
};

#endif // GEARBOX_H
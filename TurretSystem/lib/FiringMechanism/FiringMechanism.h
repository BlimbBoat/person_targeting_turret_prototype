#ifndef FIRINGMECHANISM_H
#define FIRINGMECHANISM_H

#include "ServoController.h"

namespace TurretSystem
{
    class FiringMechanism
    {
    public:
        FiringMechanism();
        FiringMechanism(int pin_trigger);
        ~FiringMechanism() = default;

        void Attach(int pin_trigger);
        void Reset();
        void FireOnce();
        void FireMultipleTimes(int amount);
    private:
        ServoController servo_controller;  
        const int servo_rotation = 0; //Needs to be adjusted to physical design  
    };
}

#endif
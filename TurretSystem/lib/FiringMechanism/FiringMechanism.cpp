#include "FiringMechanism.h"

namespace TurretSystem
{
    FiringMechanism::FiringMechanism()
    {
        //Do nothing
    }

    FiringMechanism::FiringMechanism(int pin_trigger)
    {
        Attach(pin_trigger);
    }

    void FiringMechanism::Attach(int pin_trigger)
    {
        servo_controller.Attach(pin_trigger);
    }

    void FiringMechanism::Reset()
    {
        servo_controller.ResetPosition();
    }

    void FiringMechanism::FireOnce()
    {
        servo_controller.TurnServo(servo_rotation);
        servo_controller.ResetPosition();
    }

    void FiringMechanism::FireMultipleTimes(int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            FireOnce();
        }
    }
}
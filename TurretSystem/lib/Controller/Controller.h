#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AimingMechanism.h"
#include "FiringMechanism.h"
#include "TurretStates.h"
#include "SerialCommunication.h"

namespace TurretSystem
{
    class Controller
    {
    public:
        Controller();
        Controller(int baud_rate, int pin_horizontal, int pin_vertical, int pin_trigger);
        ~Controller() = default;

        void Attach(int baud_rate, int pin_horizontal, int pin_vertical, int pin_trigger);
        void Run();
    private:
        const int max_message_size = 9;
        char messsage_response = 'A';
        char* message;

        Point target;
        const int range_difference_in_pixels = 10;

        const int surveillance_movement = 15;
        unsigned long start_time;
        unsigned long elapsed_time;
        const unsigned long time_difference = 0;

        TurretStates current_state;

        SerialCommunication serial_communication;

        AimingMechanism aiming_mechanism;
        FiringMechanism firing_mechanism;

        void WriteResponse();
    };
}

#endif
#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

namespace TurretSystem
{
    class ServoController
    {
    public:
        const int max_position = 180;
        const int middle_position = 90;
        const int min_position = 0;

        ServoController();
        ServoController(int pin_servo);
        void Attach(int pin_servo);
        void ResetPosition();
        void TurnServo(int degrees);
        int GetServoPositionInDegrees();
    private:
        unsigned long start_time;
        unsigned long elapsed_time;
        const unsigned long time_difference = 500;

        Servo servo;
        int current_position;
    };
}

#endif
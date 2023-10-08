#include "ServoController.h"

#include <Arduino.h>

namespace TurretSystem
{
    ServoController::ServoController()
    {
        //Do nothing
    }

    ServoController::ServoController(int pin_servo)
    {
        Attach(pin_servo);
    }
    
    void ServoController::Attach(int pin_servo)
    {
        current_position = 0;
        servo.attach(pin_servo);
        start_time = millis();
    }

    void ServoController::ResetPosition()
    {
        current_position = middle_position;
        servo.write((current_position)); 
    }

    void ServoController::TurnServo(int degrees)
    {
        elapsed_time = millis() - start_time;
        while (elapsed_time < time_difference)
        {
            //Do nothing
            elapsed_time = millis() - start_time;
        }
        start_time = millis();

        if(degrees < min_position)
        {
            degrees = min_position;
        }

        if(degrees > max_position)
        {
            degrees = max_position;
        }
        
        current_position = degrees;
        servo.write(current_position);       
    }

    int ServoController::GetServoPositionInDegrees()
    {
        return current_position;
    }
}


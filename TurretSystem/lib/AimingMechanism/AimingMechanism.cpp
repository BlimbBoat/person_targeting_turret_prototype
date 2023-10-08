#include "AimingMechanism.h"

#include <Arduino.h>

namespace TurretSystem
{
    AimingMechanism::AimingMechanism()
    {
        //Do nothing
    }

    AimingMechanism::AimingMechanism(int pin_horizontal, int pin_vertical)
    {
        servo_controller_horizontal.Attach(pin_horizontal);
        servo_controller_vertical.Attach(pin_vertical);
    }

    void AimingMechanism::Attach(int pin_horizontal, int pin_vertical)
    {
        servo_controller_horizontal.Attach(pin_horizontal);
        servo_controller_vertical.Attach(pin_vertical);
    }

    void AimingMechanism::Reset()
    {
        servo_controller_horizontal.ResetPosition();
        servo_controller_vertical.ResetPosition();
    }

    void AimingMechanism::MoveByDegrees(Point point)
    {
        //Move X first and then Y
        servo_controller_horizontal.TurnServo(point.x);
        servo_controller_vertical.TurnServo(point.y);
    }

    void AimingMechanism::MoveToPoint(Point point)
    {
        Point current_servo_position(0,0);
        //Move X first and then Y

        // Serial.print("Received Point: ");
        // Serial.println(point.x);

        int horizontal_distance = -1*(gun_point.x - point.x);
        int vertical_distance = -1*(gun_point.y - point.y);

        // Serial.print("Horizontal Distance in Pixels: ");
        // Serial.println(horizontal_distance);

        current_servo_position.x = servo_controller_horizontal.GetServoPositionInDegrees();
        current_servo_position.y = servo_controller_vertical.GetServoPositionInDegrees();

        // Serial.print("Current Position: ");
        // Serial.println(current_servo_position.x);

        horizontal_distance = current_servo_position.x - (horizontal_distance/pixels_to_degree_ratio);
        vertical_distance = current_servo_position.y - (vertical_distance/pixels_to_degree_ratio);

        // Serial.print("The position it needs to move to: ");
        // Serial.println(horizontal_distance);

        servo_controller_horizontal.TurnServo(horizontal_distance);
        servo_controller_vertical.TurnServo(vertical_distance);
    }

    Point AimingMechanism::ReturnServoPosition()
    {
        return Point(servo_controller_horizontal.GetServoPositionInDegrees(),servo_controller_vertical.GetServoPositionInDegrees());
    }

    int AimingMechanism::ReturnMinPosition()
    {
        return servo_controller_horizontal.min_position;
    }

    int AimingMechanism::ReturnMaxPosition()
    {
        return servo_controller_horizontal.max_position;
    }
}
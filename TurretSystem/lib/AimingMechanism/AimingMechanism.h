#ifndef AIMINGMECHANISM_H
#define AIMINGMECHANISM_H

#include "ServoController.h"
#include "Point.h"

namespace TurretSystem
{
    class AimingMechanism
    {
    public:
        const Point gun_point = Point(320,240);

        AimingMechanism();
        AimingMechanism(int pin_horizontal, int pin_vertical);
        ~AimingMechanism() = default;

        void Attach(int pin_horizontal, int pin_vertical);
        void Reset();
        void MoveByDegrees(Point point);
        void MoveToPoint(Point point);
        Point ReturnServoPosition();
        int ReturnMinPosition();
        int ReturnMaxPosition();
    private:
        ServoController servo_controller_horizontal; 
        ServoController servo_controller_vertical;
        
        const float pixels_to_degree_ratio = 8.6;
    };
}

#endif
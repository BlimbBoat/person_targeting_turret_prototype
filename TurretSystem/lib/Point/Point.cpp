#include "Point.h"

namespace TurretSystem
{
    Point::Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point::Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
}
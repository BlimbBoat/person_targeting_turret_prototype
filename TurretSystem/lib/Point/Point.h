#ifndef POINT_H
#define POINT_H

namespace TurretSystem
{
    class Point
    {
    public:
        int x;
        int y;

        Point();
        Point(int x, int y);
        ~Point() = default;
    };
}

#endif
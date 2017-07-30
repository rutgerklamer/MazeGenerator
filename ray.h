#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "vector.h"

class Ray
{
    Vector origin, direction;
    public:
        Ray();
        Ray(Vector o, Vector d);
        virtual ~Ray();

        Vector getRayOrigin () { return origin; }
        Vector getRayDirection () { return direction; }
};

#endif // RAY_H

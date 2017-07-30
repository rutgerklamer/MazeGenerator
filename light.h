#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include "vector.h"
#include "color.h"

class Light
{
    Vector position;
    Color color;
    public:
        Light();
        Light(Vector o, Color c);
        virtual ~Light();

        Vector getLightPosition () { return position; }
        Color getLightColor () { return color; }
};

#endif // LIGHT_H

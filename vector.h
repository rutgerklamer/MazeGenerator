#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
class Vector
{
    float x,y,z;
    public:
        Vector();
        Vector(float i, float j, float k);

        float getX(){ return x; };
        float getY(){ return y; };
        float getZ(){ return z; };
        void setX(int r) { x = r; };
        void setY(int t) { y = t; };
        void setZ(int y) { z = y; };

        float magnitude() {
          return sqrt((x*x) + (y*y) + (z*z));
        }

        Vector normalize() {
          float magnitude = sqrt((x*x) + (y*y) + (z*z));
          return Vector(x/magnitude, y / magnitude, z / magnitude);
        }

        Vector invert()
        {
          return Vector(-x,-y,-z);
        }

        float dot(Vector v)
        {
          return x*v.getX() + y*v.getY() + z*v.getZ();
        }

        Vector cross(Vector v)
        {
          return Vector(y*v.getZ()-z*v.getY(), z*v.getX()- x*v.getZ(), x*v.getY() - y*v.getX());
        }

        Vector add(Vector v)
        {
          return Vector(x+v.getX(), y+v.getY(), z+v.getZ());
        }
        Vector scale(float scale)
        {
          return Vector(x*scale, y*scale, z*scale);
        }
};

#endif // VECTOR_H

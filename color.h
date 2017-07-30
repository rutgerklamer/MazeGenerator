#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vector.h"

class Color
{
    public:
      float r,g,b,s;
        Color();
        Color(float e, float h, float t, float y);
        virtual ~Color();
        float getColorR() {return r;}
        float getColorG() {return g;}
        float getColorB() {return b;}
        float getColorS() {return s;}

        void setRed(float c) { r = c; }
        void setGreen(float c) { g = c; }
        void setBlue(float c) { b = c; }
        void setSpecial(float c) { s = c; }
};

#endif // COLOR_H

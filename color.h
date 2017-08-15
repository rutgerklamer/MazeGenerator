#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color
{
    public:
        float r,g,b,s;
        Color();
        Color(float e, float h, float t, float y);
        virtual ~Color();
        float getR() {return r;}
        float getG() {return g;}
        float getB() {return b;}
        float getS() {return s;}

        void setR(float c) { r = c; }
        void setG(float c) { g = c; }
        void setB(float c) { b = c; }
        void setS(float c) { s = c; }
};

#endif // COLOR_H

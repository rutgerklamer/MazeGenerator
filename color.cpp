#include "color.h"

Color::Color()
{
    r = 0.5f;
    g = 0.5f;
    b = 0.5f;
    s = 0.5f;
}

Color::Color(float e, float h, float t, float y)
{
    r = e;
    g = h;
    b = t;
    s = y;
}

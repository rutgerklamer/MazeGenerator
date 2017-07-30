#include "light.h"

Light::Light()
{
    std::cout << "Light initialized" << std::endl;
    position  = Vector(0,0,0);
    color = Color(1,0,0,0);
}

Light::Light(Vector o, Color c)
{
    std::cout << "Light initialized" << std::endl;
    position  = o;
    color  = c;
}

Light::~Light()
{

}

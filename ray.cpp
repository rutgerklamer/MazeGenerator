#include "ray.h"

Ray::Ray()
{
    std::cout << "Ray initialized" << std::endl;
    origin  = Vector(0,0,0);
    direction  = Vector(1,0,0);
}

Ray::Ray(Vector o, Vector d)
{
    std::cout << "Ray initialized" << std::endl;
    origin  = o;
    direction  = d;
}

Ray::~Ray()
{

}

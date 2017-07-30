#include "vector.h"

Vector::Vector()
{
    std::cout << "Vector initialized" << std::endl;
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(float i, float j, float k)
{
    std::cout << "Vector initialized" << std::endl;
    x = i;
    y = j;
    z = k;
}

Vector::~Vector()
{

}

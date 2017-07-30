#include "camera.h"

Camera::Camera()
{
    std::cout << "Camera initialized" << std::endl;
    camPos = Vector(0,0,0);
    camDir = Vector(0,0,1);
    camRight = Vector(0,0,0);
    camDown = Vector(0,0,0);
}

Camera::Camera(Vector p, Vector d, Vector r, Vector dw)
{
    std::cout << "Camera initialized" << std::endl;
    camPos = p;
    camDir = d;
    camRight = r;
    camDown = dw;
}


Camera::~Camera()
{

}

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "vector.h"

class Camera
{
    public:
      Vector camPos, camDir, camRight, camDown;
        Camera();
        Camera(Vector p, Vector d, Vector r, Vector dw);
        virtual ~Camera();
        Vector getCameraPosition() {return camPos;}
        Vector getCameraDirection() {return camDir;}
        Vector getCameraRight() {return camRight;}
        Vector getCameraDown() {return camDown;}
};

#endif // CAMERA_H

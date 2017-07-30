#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "light.h"

struct color {
  float r;
  float g;
  float b;
};

void savebmp(const char* filename, int w, int h, int dpi, color* data);

int thisone;

int main(int argc, char* argv[])
{
  int dpi = 72;
  int width = 640;
  int height = 480;
  int n = width*height;
  color *pixels = new color[n];

  Vector X(1,0,0);
  Vector Y(0,1,0);
  Vector Z(0,0,1);

  Vector look_at(0,0,0);
  Vector camPos (3,1.5, -4);
  Vector diff_btw(camPos.getX() - look_at.getX(), camPos.getY() - look_at.getY(), camPos.getZ() - look_at.getZ());

  Vector camDir = diff_btw.invert().normalize();
  Vector camRight = Y.cross(camDir).normalize();
  Vector camDown = camRight.cross(camDir);
  Camera m_cam(camPos, camDir, camRight, camDown);

  Color m_white_light(1,1,1,0);
  Color m_pretty_green(0.5,1.0,0.5,0.3);
  Color m_gray(0.5,0.5,0.5,0);
  Color m_black(0,0,0,0);

  Vector light_position(-7,10,-10);
  Light m_main_light(light_position, m_white_light);

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      thisone = y*width+x;
      std::cout << x % 2;
      if (x % 2 == 0 || y % 2 == 0)
      {
        pixels[thisone].r = 1 - x / width;
        pixels[thisone].g = 1 - x / width;
        pixels[thisone].b = 1 - x / width;
      } else {
        pixels[thisone].r = 0;
        pixels[thisone].g = 0;
        pixels[thisone].b = 0;
      }
    }
  }
  savebmp("render.bmp", width, height, dpi, pixels);
  std::cout << "Hello world" << "\n";
  return 0;
}

void savebmp(const char* filename, int w, int h, int dpi, color* data)
{
  FILE* f;
  int k = w*h;
  int s = 4*k;
  int filesize = 54+s;
  float factor = 39.375f;
  int m = static_cast<int>(factor);

  int ppm = dpi*m;

  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

  bmpfileheader[2] = (unsigned char)(filesize);
  bmpfileheader[3] = (unsigned char)(filesize>>8);
  bmpfileheader[4] = (unsigned char)(filesize>>16);
  bmpfileheader[5] = (unsigned char)(filesize>>24);

  bmpinfoheader[4] = (unsigned char)(w);
  bmpinfoheader[5] = (unsigned char)(w>>8);
  bmpinfoheader[6] = (unsigned char)(w>>16);
  bmpinfoheader[7] = (unsigned char)(w>>24);

  bmpinfoheader[8] = (unsigned char)(h);
  bmpinfoheader[9] = (unsigned char)(h>>8);
  bmpinfoheader[10] = (unsigned char)(h>>16);
  bmpinfoheader[11] = (unsigned char)(h>>24);

  bmpinfoheader[21] = (unsigned char)(s);
  bmpinfoheader[22] = (unsigned char)(s>>8);
  bmpinfoheader[23] = (unsigned char)(s>>16);
  bmpinfoheader[24] = (unsigned char)(s>>24);

  bmpinfoheader[25] = (unsigned char)(ppm);
  bmpinfoheader[26] = (unsigned char)(ppm>>8);
  bmpinfoheader[27] = (unsigned char)(ppm>>16);
  bmpinfoheader[28] = (unsigned char)(ppm>>24);

  bmpinfoheader[29] = (unsigned char)(ppm);
  bmpinfoheader[30] = (unsigned char)(ppm>>8);
  bmpinfoheader[31] = (unsigned char)(ppm>>16);
  bmpinfoheader[32] = (unsigned char)(ppm>>24);

  f = fopen(filename, "wb");

  fwrite(bmpfileheader, 1,14, f);
  fwrite(bmpinfoheader,1,40,f);

  for (int i = 0; i < k; i++)
  {
    color rgb = data[i];

    float red = (data[i].r)*255;
    float green = (data[i].g)*255;
    float blue = (data[i].b)*255;

    unsigned char colors[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};

    fwrite(colors,1,3,f);
  }
  fclose(f);
}

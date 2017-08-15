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

#include "color.h"
#include "vector.h"
#include "maze.h"
struct color {
  float r;
  float g;
  float b;
};

void savebmp(const char* filename, int w, int h, int dpi, color* data);

int thisone;
Maze* maze;

int main(int argc, char* argv[])
{
  srand(time(NULL));
  int difficulty = 10;
  int width = 10 * difficulty;
  int height = 10 * difficulty;
  int dpi = 72;

  int n = width*height;
  color* randomMaze = new color[n];
  color* solvedMaze = new color[n];

  maze = new Maze(width, height);
  while (maze->totalPinks < 10) {
    delete maze; srand(3289 * time(NULL)); maze = new Maze(width, height);
  }
  std::cout << "Hello world" << "\n";

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      thisone = y*width+x;
      randomMaze[thisone].r = maze->getPixel(x,y)->getR();
      randomMaze[thisone].g = maze->getPixel(x,y)->getG();
      randomMaze[thisone].b = maze->getPixel(x,y)->getB();
    }
  }
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      thisone = y*width+x;
      solvedMaze[thisone].r = maze->getPixelSolved(x,y)->getR();
      solvedMaze[thisone].g = maze->getPixelSolved(x,y)->getG();
      solvedMaze[thisone].b = maze->getPixelSolved(x,y)->getB();
    }
  }
  savebmp("randomMaze.bmp", width, height, dpi, randomMaze);
  savebmp("solvedMaze.bmp", width, height, dpi, solvedMaze);
  std::cout << "Hello world" << "\n";
  delete maze;
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

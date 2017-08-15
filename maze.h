#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include "stdlib.h"
#include "vector.h"
#include "color.h"
class Maze
{
    public:
        Maze(int w, int h);
        ~Maze();
        bool GenerateMazeHard();
        Color* getPixel(int x, int y);
        enum Dir
        {
          N, W ,S, E
        };
        void Paint(Dir dir);
        enum Difficulty
        {
          EASY, NORMAL, HARD
        };
        struct Cell {
          Color* color;
          Vector position;
          bool visited = false;
        };
        std::vector<std::vector<Cell*>> cells;
        std::vector<Cell*> visitedStack;
        Vector walkerPos;
        Vector start;
        Vector end;
        Vector nextMove;
        int lol;
        Vector resolution;
};

#endif // MAZE_H

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include "vector.h"
#include "color.h"
class Maze
{
    public:
        Maze(int w, int h);
        ~Maze();
        bool GenerateMaze();
        bool GenerateSolvedMaze();
        Color getPixel(int x, int y);
        Color getPixelSolved(int x, int y);
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
          Color color;
          Color solvedColor;
          Vector position;
          bool visited = false;
        };
        std::vector<std::vector<Cell>> cells;
        std::vector<Cell*> visitedStack;
        Vector walkerPos;
        Vector start;
        Vector end;
        Vector nextMove;
        int totalPinks;
        Vector resolution;
};

#endif // MAZE_H

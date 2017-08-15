#include "maze.h"

Maze::Maze(int w, int h)
{
    srand(time(NULL));
    std::cout << "Maze initialized" << std::endl;
    resolution.setX(w);
    resolution.setY(h);

    for (int x = 0; x < resolution.getX() - 1; x++)
    {
      std::vector<Cell*> row;
      for (int y = 0; y < resolution.getY() - 1; y++)
      {
        Cell* madeCell = new Cell();
        madeCell->color = new Color();
        madeCell->solvedColor = new Color();
        madeCell->position = Vector(x,y,0);
        madeCell->color->setR(1);
        madeCell->color->setG(1);
        madeCell->color->setB(1);
        row.push_back(madeCell);
      }
      cells.push_back(row);
    }
    for (unsigned int x = 0; x < resolution.getX()/2 ; x++)
    {
      for (unsigned int y = 0; y < resolution.getY()/2; y++)
      {
          cells[x*2.0][y*2.0]->color->setR(0);
          cells[x*2.0][y*2.0]->color->setG(0);
          cells[x*2.0][y*2.0]->color->setB(0);
      }
    }

    int x = (resolution.getX()) / 2 - 1;
    int y = (resolution.getY()) / 2 - 1;
    std::cout << x << "      " << y << std::endl;
    walkerPos = Vector(x,y,0);
    end = Vector(x,y,0);
    cells[x][y]->visited = true;
    visitedStack.push_back(cells[x][y]);

    while (GenerateMaze()){}
    while (true)
    {
      float X = rand() % (int)(resolution.getX()-1);
      float Y = rand() % (int)(resolution.getY()-1);
      if (cells[X][Y]->color->getR() == 1)
      {
        cells[X][Y]->color->setR(0);
        cells[X][Y]->color->setG(1);
        cells[X][Y]->color->setB(0);
        start = Vector(X,Y,0);
        break;
      }
    }

    for (unsigned int x = 0; x < resolution.getX()-1; x++)
    {
      for (unsigned int y = 0; y < resolution.getY()-1; y++)
      {
        cells[x][y]->solvedColor->setR(cells[x][y]->color->getR());
        cells[x][y]->solvedColor->setG(cells[x][y]->color->getG());
        cells[x][y]->solvedColor->setB(cells[x][y]->color->getB());
        cells[x][y]->visited = false;
      }
    }
    walkerPos.setX(start.getX());
    walkerPos.setY(start.getY());
    std::cout << " X ( " << walkerPos.getX() << " ) Y ( " << walkerPos.getY() << " )" << std::endl;
    cells[walkerPos.getX()][walkerPos.getY()]->visited = true;
    visitedStack.push_back(cells[walkerPos.getX()][walkerPos.getY()]);
    cells[end.getX()][end.getY()]->color->setR(1);
    cells[end.getX()][end.getY()]->color->setG(0);
    cells[end.getX()][end.getY()]->color->setB(0);
    while (GenerateSolvedMaze()){}
    for (int x = 0; x < resolution.getX(); x++)
    {
      for (int y = 0; y < resolution.getY(); y++)
      {
        if (x + 1 < resolution.getX()-1
         && y + 1 < resolution.getY()-1
         &&  y - 1 >= 0
         &&  x - 1 >= 0)
         {
           int visitedNeighbourBacktrackCount = 0;
           if (cells[x+1][y]->solvedColor->getG() == 0 && cells[x+1][y]->solvedColor->getR() == 1)
           {
             visitedNeighbourBacktrackCount++;
           }
           if (cells[x-1][y]->solvedColor->getG() == 0 && cells[x-1][y]->solvedColor->getR() == 1  )
           {
             visitedNeighbourBacktrackCount++;
           }
           std::cout << x << "   " << y << std::endl;
           if (cells[x][y+1]->solvedColor->getG() == 0 && cells[x][y+1]->solvedColor->getR() == 1)
           {
             visitedNeighbourBacktrackCount++;
           }
           if (cells[x][y-1]->solvedColor->getG() == 0 && cells[x][y-1]->solvedColor->getR() == 1  )
           {
             visitedNeighbourBacktrackCount++;
           }
           if (visitedNeighbourBacktrackCount < 1 && cells[x][y]->solvedColor->getR() == 1) {
             cells[x][y]->solvedColor->setR(1);
             cells[x][y]->solvedColor->setG(1);
             cells[x][y]->solvedColor->setB(1);
           }
         }

      }
  }
}

Maze::~Maze()
{
  for (int x = 0; x < resolution.getX() - 1; x++)
  {
    for (int y = 0; y < resolution.getY() - 1; y++)
    {
      delete cells[x][y];
    }
  }
}

bool Maze::GenerateMaze()
{
    Dir direction = static_cast<Dir>(rand() % 4);
    if (direction == N)
    {
      nextMove.setX(0);
      nextMove.setY(-2);
    } else if (direction == S) {
      nextMove.setX(0);
      nextMove.setY(2);
    } else if (direction == E) {
      nextMove.setX(2);
      nextMove.setY(0);
    } else if (direction == W) {
      nextMove.setX(-2);
      nextMove.setY(0);
    }
    if (direction == N && walkerPos.getY()-2 >= 0
     || direction == S && walkerPos.getY()+2 < resolution.getY() - 1
     || direction == E && walkerPos.getX()+2 < resolution.getX() - 1
     || direction == W && walkerPos.getX()-2 >= 0)
    {
      if (!cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->visited) {
        cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->visited = true;
        visitedStack.push_back(cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]);
        end = walkerPos;
        walkerPos.setX(walkerPos.getX() + nextMove.getX());
        walkerPos.setY(walkerPos.getY() + nextMove.getY());
        Paint(direction);
      } else if (walkerPos.getX() + 2 < resolution.getX() - 1 && !cells[walkerPos.getX() + 2][walkerPos.getY()]->visited
       || walkerPos.getY() + 2 < resolution.getY() - 1 && !cells[walkerPos.getX()][walkerPos.getY() + 2]->visited
       || walkerPos.getY() - 2 >= 0 && !cells[walkerPos.getX()][walkerPos.getY() - 2]->visited
       || walkerPos.getX() - 2 >= 0 && !cells[walkerPos.getX() - 2][walkerPos.getY()]->visited)
      {
        return true;
      } else if (visitedStack.size() > 0) {
        walkerPos = visitedStack[visitedStack.size() - 1]->position;
        visitedStack.pop_back();
      } else {
        std::cout << "done" << std::endl;
        return false;
      }
  }
  return true;
}

bool Maze::GenerateSolvedMaze()
{
  Dir direction = static_cast<Dir>(rand() % 4);
  if (direction == N)
  {
    nextMove.setX(0);
    nextMove.setY(-1);
  } else if (direction == S) {
    nextMove.setX(0);
    nextMove.setY(1);
  } else if (direction == E) {
    nextMove.setX(1);
    nextMove.setY(0);
  } else if (direction == W) {
    nextMove.setX(-1);
    nextMove.setY(0);
  }
  lol++;
  std::cout << lol << std::endl;
  if (direction == N && walkerPos.getY()-1 >= 0
   || direction == S && walkerPos.getY()+1 < resolution.getY()
   || direction == E && walkerPos.getX()+1 < resolution.getX()
   || direction == W && walkerPos.getX()-1 >= 0)
  {
      if (!cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->visited && cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->color->getR() == 1) {
        cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->solvedColor->setR(1);
        cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->solvedColor->setG(0);
        cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->solvedColor->setB(1);
        cells[walkerPos.getX()][walkerPos.getY()]->solvedColor->setR(1);
        cells[walkerPos.getX()][walkerPos.getY()]->solvedColor->setG(0);
        cells[walkerPos.getX()][walkerPos.getY()]->solvedColor->setB(1);
        cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]->visited = true;
        visitedStack.push_back(cells[walkerPos.getX() + nextMove.getX()][walkerPos.getY()+nextMove.getY()]);
        walkerPos.setX(walkerPos.getX() + nextMove.getX());
        walkerPos.setY(walkerPos.getY() + nextMove.getY());
      }else if (walkerPos.getX() + 1 < resolution.getX() && !cells[walkerPos.getX() + 1][walkerPos.getY()]->visited && cells[walkerPos.getX()+1][walkerPos.getY()]->color->getR() == 1
       || walkerPos.getY() + 1 < resolution.getY() && !cells[walkerPos.getX()][walkerPos.getY() + 1]->visited && cells[walkerPos.getX()][walkerPos.getY()+1]->color->getR() == 1
       || walkerPos.getY() - 1 >= 0 && !cells[walkerPos.getX()][walkerPos.getY() - 1]->visited && cells[walkerPos.getX()][walkerPos.getY()-1]->color->getR() == 1
       || walkerPos.getX() - 1 >= 0 && !cells[walkerPos.getX() - 1][walkerPos.getY()]->visited && cells[walkerPos.getX()-1][walkerPos.getY()]->color->getR() == 1)
      {
        return true;
      } else if (visitedStack.size() > 0) {
        walkerPos = visitedStack[visitedStack.size() - 1]->position;
        visitedStack[visitedStack.size() - 1]->solvedColor->setR(1);
        visitedStack[visitedStack.size() - 1]->solvedColor->setG(1);
        visitedStack[visitedStack.size() - 1]->solvedColor->setB(1);
        visitedStack.pop_back();
      } else {
        std::cout << "done" << std::endl;
        return false;
      }
  }
  if (walkerPos.getX() == end.getX() && walkerPos.getY()  == end.getY())
  {
    cells[walkerPos.getX()][walkerPos.getY()]->solvedColor->setR(1);
    cells[walkerPos.getX()][walkerPos.getY()]->solvedColor->setG(0);
    cells[walkerPos.getX()][walkerPos.getY()]->solvedColor->setB(0);
    return false;
  }
  return true;
}

void Maze::Paint(Dir dir)
{
  if (dir == N ) {
    if (walkerPos.getY() - 1 >= 0)
    {
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setR(0);
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setG(0);
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setB(0);
    }
    if (walkerPos.getY() + 1 < resolution.getY() - 1)
    {
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setR(1);
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setG(1);
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setB(1);
    }
  }
  if (dir == S) {
    if (walkerPos.getY() + 1 < resolution.getY() - 1)
    {
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setR(0);
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setG(0);
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setB(0);
    }
    if (walkerPos.getY() - 1 >= 0)
    {
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setR(1);
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setG(1);
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setB(1);
    }
  }
  if (dir == W)
  {
    if (walkerPos.getX() - 1 >= 0)
    {
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setR(0);
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setG(0);
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setB(0);
    }
    if (walkerPos.getX() + 1 < resolution.getX() - 1)
    {
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setR(1);
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setG(1);
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setB(1);
    }
  }
  if (dir == E)
  {
    if (walkerPos.getX() + 1 < resolution.getX() - 1)
    {
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setR(0);
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setG(0);
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setB(0);
    }
    if (walkerPos.getX() - 1 >= 0)
    {
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setR(1);
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setG(1);
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setB(1);
    }
  }
  if (dir == W || dir == E)
  {
    if (walkerPos.getY() - 1 >= 0)
    {
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setR(0);
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setG(0);
      cells[walkerPos.getX()][walkerPos.getY()-1]->color->setB(0);
    }
    if (walkerPos.getY() + 1 < resolution.getY() - 1)
    {
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setR(0);
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setG(0);
      cells[walkerPos.getX()][walkerPos.getY()+1]->color->setB(0);
    }
  }
  if (dir == S || dir == N) {
    if (walkerPos.getX() - 1 >= 0)
    {
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setR(0);
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setG(0);
      cells[walkerPos.getX()-1][walkerPos.getY()]->color->setB(0);
    }
    if (walkerPos.getX() + 1 < resolution.getX() - 1)
    {
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setR(0);
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setG(0);
      cells[walkerPos.getX()+1][walkerPos.getY()]->color->setB(0);
    }
  }
}

Color* Maze::getPixel(int x, int y)
{
  Color* temp;
  if (x >= 0 && x < resolution.getX() - 1 && y < resolution.getY() - 1 && y >= 0)
  {
      return cells[x][y]->color;
  }
  return temp;
}

Color* Maze::getPixelSolved(int x, int y)
{
  Color* temp;
  if (x >= 0 && x < resolution.getX() - 1 && y < resolution.getY() - 1 && y >= 0)
  {
      return cells[x][y]->solvedColor;
  }
  return temp;
}

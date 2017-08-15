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
    end = walkerPos;
    cells[x][y]->visited = true;
    cells[x][y]->color->setR(0);
    cells[x][y]->color->setG(1);
    cells[x][y]->color->setB(0);
    visitedStack.push_back(cells[x][y]);

    while (GenerateMazeHard()){}
}

Maze::~Maze()
{

}

bool Maze::GenerateMazeHard()
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
    lol++;
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

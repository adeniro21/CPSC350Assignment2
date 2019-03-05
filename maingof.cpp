#include "gameoflife.h"
#include <iostream>

using namespace std;

int main()
{
  MakeGame grid;
  grid.provideFile();
  //grid.outputGrid();
  grid.mode();
  //grid.doughnutArray();
  //grid.outputNeighborGrid();
  return 0;
}

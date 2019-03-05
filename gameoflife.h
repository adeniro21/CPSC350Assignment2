#include <iostream>

using namespace std;

class MakeGame
{
  public:
    MakeGame();
    ~MakeGame();
    char** twodArray(int rows, int columns);
    char** neighborArray();
    void provideFile();
    void readFile(string file);
    void useRandom();
    void outputGrid();
    void outputNeighborGrid();
    void mode();
    void speed();
    void enter();
    void writeToFile();
    void playClassic();
    void playDoughnut();
    void playMirror();
    void classicArray();
    void doughnutArray();
    void mirrorArray();
    void generations();
    int neighbors(int x, int y);
};

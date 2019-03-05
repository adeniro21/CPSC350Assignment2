#include "gameoflife.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace std;

int row = 0; //row of the matrix
int column = 0; //column of the matrix
char** matrix;
char** neighborMatrix;
string fileName; // filename for write file
int generation = 0; //generation count incremented each time outputgrid function is called
int speed = 0; //determines how the user wants the output displayed
int end = 1; // end while loop in play modes

MakeGame::MakeGame()
{

}

MakeGame::~MakeGame()
{
  for (int i = 0; i < ::row; ++i)
  {
    delete [] twodArray(::row, ::column)[i];
  }
  delete [] twodArray(::row, ::column);

  for (int i = 0; i < (::row + 2); ++i)
  {
    delete [] neighborArray()[i];
  }
  delete [] neighborArray();
}

char** MakeGame::twodArray(int rows, int columns) //initialize 2darray
{
  char** initArray = new char*[rows];
  for(int i = 0; i < rows; i++)
  {
    initArray[i] = new char[columns];
  }
  return initArray;
}

char** MakeGame::neighborArray() //initial neighbor array
{
  char** neighArray = new char*[(::row + 2)];
  for(int i = 0; i < (::row + 2); i++)
  {
    neighArray[i] = new char[(::column + 2)];
  }
  return neighArray;
}

void MakeGame::provideFile() //asking if they want to provide a file or not
{
  int num = 0;
  char answer;
  cout << "would you like to provide a map file (y/n)? ";
  cin >> answer;
  while(num == 0)
  {
    if(answer == 'y')
    {
      string file;
      cout << "what is the name of the map file? ";
      cin >> file;
      readFile(file);
      num = 1;
    }
    else if(answer == 'n')
    {
      useRandom();
      num = 1;
    }
    else
    {
     cout << "Not a valid response." << endl;
     cout << "would you like to provide a map file (y/n)? ";
     cin >> answer;
   }
 }
}

void MakeGame::readFile(string file)
{
  string line;
  ifstream gridFile;
  gridFile.open(file, ios::in);
  if (gridFile.is_open())
  {
    int count = 0;
    int rowCount = 0;
    char** grid;
    while(!gridFile.eof())
    {
      getline(gridFile, line);
      count++;
      if(count == 1)
      {
        stringstream rows(line);
        rows >> ::row;
      }
      else if(count == 2)
      {
        stringstream columns(line);
        columns >> ::column;
        grid = twodArray(::row, ::column); //changed to global varaible reference
      }
      else
      {
        for (int i = rowCount; i <= rowCount; i++)
        {
          for (int j = 0; j < ::column; j++)
          {
            grid[i][j] = line[j];
          }
        }
        rowCount++;
      }
    }
    ::matrix = grid;
  }
  else
  {
    cout << "Not a valid file" << endl;
  }
  gridFile.close();
}

void MakeGame::useRandom()
{
  double density;
  cout << "How many rows do you want for the playing grid? ";
  cin >> ::row;
  cout << "How many columns do want for the playing grid? ";
  cin >> ::column;
  cout << "What is the population density (number between 0 and 1 to the hundreths place)? ";
  cin >> density;
  char** rGrid;
  rGrid = twodArray(::row, ::column); //changed to global variable reference
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      double random = ((double) rand() / (RAND_MAX));
      if(random > density)
      {
        rGrid[i][j] = '-';
      }
      else rGrid[i][j] = 'X';
    }
  }
  ::matrix = rGrid;
}

void MakeGame::outputGrid() // output matrix to screen in nicer format
{
  cout << "Generation: " << ::generation << endl;
  ::generation++;
  for (int i = 0; i < ::row; i++)
  {
    for (int j = 0; j < ::column; j++)
    {
      cout << ::matrix[i][j] << ' ';
    }
    cout << endl;
  }
  cout << " " << endl;
}

void MakeGame::outputNeighborGrid() //just checking to see if neighbor matrix was created correctly
{
  for (int i = 0; i < (::row + 2); i++)
  {
    for (int j = 0; j < (::column + 2); j++)
    {
      cout << ::neighborMatrix[i][j] << ' ';
    }
    cout << endl;
  }
  cout << " " << endl;
}

void MakeGame::mode() //selecting mode to run in
{
  int answer;
  cout << "What mode do you want to run in: [1] classic, [2] doughnut, [3] mirror? ";
  cin >> answer;
  int num = 0;
  while(num == 0)
  {
    if (answer == 1)
    {
      speed();
      playClassic();
      num = 1;
    }
    else if (answer == 2)
    {
      speed();
      playDoughnut();
      num = 1;
    }
    else if (answer == 3)
    {
      speed();
      playMirror();
      num = 1;
    }
    else
    {
     cout << "Not a valid response." << endl;
     cout << "What mode do you want to run in: [1] classic, [2] doughnut, [3] mirror? ";
     cin >> answer;
   }
  }
}

void MakeGame::speed() //asking for speed game mode and changing global variable based on response
{
  int answer;
  cout << "Do you want: [1] a pause between generations, [2] to press enter between generations, or [3] output everything to a file? ";
  cin >> answer;
  int num = 0;
  while(num == 0)
  {
    if (answer == 1)
    {
      num = 1;
      ::speed = 1;
    }
    else if (answer == 2)
    {
      num = 1;
      ::speed = 2;
    }
    else if (answer == 3)
    {
      num = 1;
      cout << "What is the name of the file you want to write to? ";
      cin >> ::fileName;
      ::speed = 3;
    }
    else
    {
      cout << "Not a valid response. Enter a number" << endl;
      cout << "Do you want: [1] a pause between generations, [2] to press enter between generations, or [3] output everything to a file? ";
      cin >> answer;
    }
  }
}

void MakeGame::enter()
{
  cout << "press ENTER to continue..." << endl;
  cin.get();
  //cin.ignore();
}

void MakeGame::writeToFile() //writing to file specified in mode
{
  ofstream wfile;
  wfile.open(::fileName, fstream::app);
  wfile << "Generation: " << ::generation << endl;
  ::generation++;
  for (int i = 0; i < ::row; i++)
  {
    for (int j = 0; j < ::column; j++)
    {
      wfile << ::matrix[i][j] << ' ';
    }
    wfile << endl;
  }
  wfile << " " << endl;

}

void MakeGame::playClassic()
{
  //enter();
  if(::speed != 3)
  {
    outputGrid(); // generation 0
    classicArray(); // contructing neighbor matrix
  }
  else
  {
    writeToFile();
    classicArray();
  }
  //outputNeighborGrid();
  while(::end == 1)
  {
    if(::speed == 1) // 1 second pause between generations
    {
      sleep(1);
      generations();
      classicArray();
    }
    if(::speed == 2) // press enter to continue
    {
      enter();
      generations();
      classicArray();
    }
    if(::speed == 3) //write to a file
    {
      generations();
      classicArray();
      writeToFile();
    }
  }
}

void MakeGame::playDoughnut()
{
  //enter();
  if(::speed != 3)
  {
    outputGrid(); // generation 0
    doughnutArray(); // contructing neighbor matrix
  }
  else
  {
    writeToFile();
    doughnutArray();
  }
  //outputNeighborGrid();
  while(::end == 1)
  {
    if(::speed == 1) // 1 second pause between generations
    {
      sleep(1);
      generations();
      doughnutArray();
    }
    if(::speed == 2) // press enter to continue
    {
      enter();
      generations();
      doughnutArray();
    }
    if(::speed == 3) //write to a file
    {
      generations();
      doughnutArray();
      writeToFile();
    }
  }
}

void MakeGame::playMirror()
{
  //enter();
  if(::speed != 3)
  {
    outputGrid(); // generation 0
    mirrorArray(); // contructing neighbor matrix
  }
  else
  {
    writeToFile();
    mirrorArray();
  }
  //outputNeighborGrid();
  while(::end == 1)
  {
    if(::speed == 1) // 1 second pause between generations
    {
      sleep(1);
      generations();
      mirrorArray();
    }
    if(::speed == 2) // press enter to continue
    {
      enter();
      generations();
      mirrorArray();
    }
    if(::speed == 3) //write to a file
    {
      generations();
      mirrorArray();
      writeToFile();
    }
  }
}


void MakeGame::classicArray() //matrix that physically creates the neighbor matrix in classic mode
{
  char** classArray;
  classArray = neighborArray();
  classArray[0][0] = '-'; //top left corner
  classArray[0][(::column + 1)] = '-'; // top right corner
  classArray[(::row + 1)][0] = '-'; // bottom left corner
  classArray[(::row + 1)][(::column + 1)] = '-'; //bottom right corner

  for (int i = 0; i < 1; i++) //fill first row
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      classArray[i][j] = '-';
    }
  }

  for (int i = (::row + 1); i < (::row + 2); i++) //fill last row
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      classArray[i][j] = '-';
    }
  }

  for (int i = 1; i < (::row + 1); i++) //fill first column
  {
    for (int j = 0; j < 1; j++)
    {
      classArray[i][j] = '-';
    }
  }

  for (int i = 1; i < (::row + 1); i++) //fill last column
  {
    for (int j = (::column + 1); j < (::column + 2); j++)
    {
      classArray[i][j] = '-';
    }
  }

  for (int i = 1; i < (::row + 1); i++) //double for loop to match original matrix
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      classArray[i][j] = ::matrix[(i - 1)][(j - 1)];
    }
  }
  ::neighborMatrix = classArray;
}

void MakeGame::doughnutArray() //matrix that physically creates the neighbor matrix in doughnut mode
{
  char** doughArray;
  doughArray = neighborArray();
  doughArray[0][0] = ::matrix[(::row - 1)][(::column - 1)]; //top left corner
  doughArray[0][(::column + 1)] = ::matrix[(::row - 1)][0]; // top right corner
  doughArray[(::row + 1)][0] = ::matrix[0][(::column - 1)]; // bottom left corner
  doughArray[(::row + 1)][(::column + 1)] = ::matrix[0][0]; //bottom right corner

  for (int i = 0; i < 1; i++) //fill first row
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      doughArray[i][j] = ::matrix[(::row - 1)][(j - 1)];
    }
  }

  for (int i = (::row + 1); i < (::row + 2); i++) //fill last row
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      doughArray[i][j] = ::matrix[0][(j - 1)];
    }
  }

  for (int i = 1; i < (::row + 1); i++) //fill first column
  {
    for (int j = 0; j < 1; j++)
    {
      doughArray[i][j] = ::matrix[(i - 1)][(::column - 1)];
    }
  }

  for (int i = 1; i < (::row + 1); i++) //fill last column
  {
    for (int j = (::column + 1); j < (::column + 2); j++)
    {
      doughArray[i][j] = ::matrix[(i - 1)][0];
    }
  }

  for (int i = 1; i < (::row + 1); i++) //double for loop to match original matrix
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      doughArray[i][j] = ::matrix[(i - 1)][(j - 1)];
    }
  }
  ::neighborMatrix = doughArray;
}

void MakeGame::mirrorArray() //matrix that physically creates the neighbor matrix in mirror mode
{
  char** mirroArray;
  mirroArray = neighborArray();
  mirroArray[0][0] = ::matrix[0][0]; //top left corner
  mirroArray[0][(::column + 1)] = ::matrix[0][(::column - 1)]; // top right corner
  mirroArray[(::row + 1)][0] = ::matrix[(::row - 1)][0]; // bottom left corner
  mirroArray[(::row + 1)][(::column + 1)] = ::matrix[(::row - 1)][(::column - 1)]; //bottom right corner

  for (int i = 0; i < 1; i++) //fill first row
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      mirroArray[i][j] = ::matrix[0][(j - 1)];
    }
  }

  for (int i = (::row + 1); i < (::row + 2); i++) //fill last row
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      mirroArray[i][j] = ::matrix[(::row - 1)][(j - 1)];
    }
  }

  for (int i = 1; i < (::row + 1); i++) //fill first column
  {
    for (int j = 0; j < 1; j++)
    {
      mirroArray[i][j] = ::matrix[(i - 1)][0];
    }
  }

  for (int i = 1; i < (::row + 1); i++) //fill last column
  {
    for (int j = (::column + 1); j < (::column + 2); j++)
    {
      mirroArray[i][j] = ::matrix[(i - 1)][(::column - 1)];
    }
  }

  for (int i = 1; i < (::row + 1); i++) // match original matrix withing middle
  {
    for (int j = 1; j < (::column + 1); j++)
    {
      mirroArray[i][j] = ::matrix[(i - 1)][(j - 1)];
    }
  }
  ::neighborMatrix = mirroArray;
}

void MakeGame::generations() //creates temporary matrix to replace original matrix using the game rules
{
  int stable = 0;
  int empty = 0;
  char** tempMatrix;
  tempMatrix = twodArray(::row, ::column);
  for(int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      char loc = ::matrix[i][j];
      int neighbor = neighbors((i + 1), (j + 1));
      if(loc == '-' && neighbor == 3)
      {
        tempMatrix[i][j] = 'X';
      }
      else if(loc == 'X' && neighbor < 2)
      {
        tempMatrix[i][j] = '-';
      }
      else if(loc == 'X' && neighbor > 3)
      {
        tempMatrix[i][j] = '-';
      }
      else
      {
        tempMatrix[i][j] = loc;
      }
    }
  }

  for (int i = 0; i < ::row; i++) //checking for stability
  {
    for (int j = 0; j < ::column; j++)
    {
      if(tempMatrix[i][j] == ::matrix[i][j])
      {
        stable++;
        if(stable == ::row * ::column)
        {
          if(::speed != 3)
          {
            outputGrid();
          }
          cout << "Life has become stable" << endl;
          cout << "simulation complete" << endl;
          enter();
          ::end = 0;
        }
      }
    }
  }

  for (int i = 0; i < ::row; i++) //checking for empty
  {
    for (int j = 0; j < ::column; j++)
    {
      if(tempMatrix[i][j] == '-')
      {
        empty++;
        if(empty == ::row * column)
        {
          if(::speed != 3)
          {
            outputGrid();
          }
          cout << "Life has died out" << endl;
          cout << "simulation complete" << endl;
          enter();
          ::end = 0;
        }
      }
    }
  }
  ::matrix = tempMatrix;
  if(::speed != 3)
  {
    if(::end == 1)
    {
      outputGrid();
    }
  }
}

int MakeGame::neighbors(int x, int y) //iterates through 3X3 matrix given a specified index
{
  int sum = 0;
  for (int i = -1; i < 2; i++)
  {
    for (int j = -1; j < 2; j++)
    {
      int ro = (x + i);
      int col = (y + j);
      if(::neighborMatrix[ro][col] == 'X') //adds to sum if neighbor is alive
      {
        sum += 1;
      }
    }
  }
  if(::neighborMatrix[x][y] == 'X') //subtarcts from sum if given index is alive
  {
    sum -= 1;
  }
  return sum;
}

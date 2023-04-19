#include <iostream>

using namespace std;

void deleteNumbers (bool tab[9][9][10], int number, int row, int column)
{
  // Take down all posibilites for number in row, column and square

  //deleting from row and column
  for (int x = 0; x < 9; x++)
    {
      tab[row][x][number] = false;
      tab[x][column][number] = false;
    }

  //deleting from square
  //taking down row/column to 0, 1 or 2
  int row2 = row;
  int column2 = column;
  row = row / 3;
  column = column / 3;

  // making them 0, 3 or 6 - coordinates of left upper corner of every square
  row = row * 3;
  column = column * 3;

  for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
	    {
	        tab[row + x][column + y][number] = false;
	    }
    }
    tab[row2][column2][number] = true;
}

bool checkDetermined (bool tab[9][9][10], int row, int column, int solution[9][9])
{
    //function will check if we can determine which number is in square and, if yes, will write it to solution
    if (tab[row][column][0] == 1)
    {
        for (int i = 1; i < 10; i++)
        {
            if (tab[row][column][i] == 1)
            {
                solution[row][column] = i;
                return true;
            }
        }
        return false;
    }
    else
    {
        int index;
        int how_much_ones = 0;
        
        for (int i = 1; i < 10; i++)
        {
            if (tab[row][column][i] == 1)
            {
                index = i;
                how_much_ones++;
            }
        }
        
        if (how_much_ones == 1)
        {
            tab[row][column][0] = 1;
            solution[row][column] = index;
            return true;
        }

        return false;
    }
}

bool checkWin (int solution[9][9])
{
    //Function will check, if in every square there is a digit
    for (int x = 0; x<9; x++)
    {
        for (int y = 0; y<9; y++)
            if (solution[x][y]== 0)
            {
                return false;
            }
    }
    return true;
}

void printTable (int tab[9][9])
{
    for (int i = 0; i<9; i++)
    {
        for (int y = 0; y<9; y++)
        {
            if (tab[i][y] ==0)
            {
                cout << "  ";
            }
            else
            {
                cout << tab[i][y] << " ";
            }
            if (y%3 == 2)
            {
                cout << "   ";
            }
        }
        cout << endl;
        if (i%3 == 2)
        {
            cout << endl;
        }
    }
}


main ()
{
  //arrays: t[row][column]

  //make sudoku
  
    int sudoku[9][9] = {
    {0, 3, 0,   0, 1, 0,    0, 6, 0},
    {7, 5, 0,   0, 3, 0,    0, 4, 8},
    {0, 0, 6,   9, 8, 4,    3, 0, 0},
    
    {0, 0, 3,   0, 0, 0,    8, 0, 0},
    {9, 1, 2,   0, 0, 0,    6, 7, 4},
    {0, 0, 4,   0, 0, 0,    5, 0, 0},
    
    {0, 0, 1,   6, 7, 5,    2, 0, 0},
    {6, 8, 0,   0, 9, 0,    0, 1, 5},
    {0, 9, 0,   0, 4, 0,    0, 3, 0},
  };

  /*make list of cases
     if bool_sudoku[0][0][3] = 1, there is possible that 3 can be in left corner, if 0, there is definitely not
     [x][y][0] could be used as flag, if number is determined.
     
     Now we making a booltable based on our sudoku
   */
  bool bool_sudoku[9][9][10];
  for (int x = 0; x < 9; x++)
    {
          for (int y = 0; y < 9; y++)
    	{
    	    if (sudoku[x][y] == 0)
    	    {
        	    bool_sudoku[x][y][0] = 0;
        	    for (int z = 1; z < 10; z++)
        	    {
        	      bool_sudoku[x][y][z] = 1;
        	    }
    	    }
    	    else
    	    {
    	        bool_sudoku[x][y][0] = 1;
        	    for (int z = 1; z < 10; z++)
        	    {
        	      bool_sudoku[x][y][z] = 0;
        	    }
        	    //mark number 
        	    bool_sudoku[x][y][sudoku[x][y]] = 1;
    	    }
    	}
    }
    
    printTable(sudoku);
    //From that moment i will try to solve sudoku
    
    bool is_not_solve = 1;
    int zmienna = 0;
    int how_long_from_last_change = 0; // counts how many times loop was executed with no change
    
    while(is_not_solve)
    {
        is_not_solve = 0;
        how_long_from_last_change++; 
        
        for (int x = 0; x<9; x++)
        {
            for (int y = 0; y<9; y++)
            {
                if (bool_sudoku[x][y][0]== 0)
                {
                    is_not_solve = 1;
                    if( checkDetermined(bool_sudoku, x, y, sudoku) )
                    {
                        how_long_from_last_change = 0;
                        zmienna = sudoku[x][y];
                        deleteNumbers(bool_sudoku, zmienna, x, y);
                    }
                }
                else
                {
                    deleteNumbers(bool_sudoku, sudoku[x][y], x, y);
                }
            }
        }
        if (how_long_from_last_change >2)
        {
            is_not_solve = 0;
        }
        
    }
    
    cout << "\n The last version program can do  (in that moment)\n";
    printTable(sudoku);
    
}










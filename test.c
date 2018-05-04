#include<stdio.h>
#include <stdbool.h>
/*
int maze[5][5] = {{0,0,0,0,0},
                  {1,1,1,1,0},
                  {0,1,0,1,0},
                  {0,1,0,1,1},
                  {0,0,0,0,0}};
int finishRow = 3;
int finishCol = 4;
int gridSize = 5;

*/

int maze[10][10] = {
  {0,0,0,0,0,0,0,0,0,0},
  {1,1,0,1,1,1,1,0,1,0},
  {0,1,0,1,0,0,1,0,1,0},
  {0,1,1,1,0,1,1,0,1,0},
  {0,1,0,1,0,1,0,0,1,0},
  {0,1,0,1,0,1,1,1,1,0},
  {0,1,0,0,0,0,0,1,0,0},
  {0,1,0,1,1,1,0,1,0,0},
  {0,1,1,1,0,1,0,1,1,1},
  {0,0,0,0,0,0,0,0,0,0}
};


int row_size = 10;
int col_size = 10;




bool solve(int row, int col) {

  if(maze[row][col] == 0 || maze[row][col] == 8){
    return false;
  }
  if(row == (row_size-2) && col == (col_size-1)){
    return true;
  }
  maze[row][col] = 8;
  if (solve(row-1, col))
    return true;

  if (solve(row, col+1))
    return true;

  if (solve(row+1, col))
    return true;

  if (solve(row, col-1))
    return true;

  maze[row][col] = 1;
  
  return false;
}

int main()
{

  solve(1, 0);

  for(int i = 0; i < row_size; i++){
    for(int j = 0; j < col_size; j++)
        if (maze[i][j] == 8){
            printf("X");
        }else{
            printf("%i",maze[i][j]);
        }
    printf("\n");
  }

}
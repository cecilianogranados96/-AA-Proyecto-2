#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int g_columnas 	= 5;
int g_filas 	= 5;

int laberinto [5][5] = {{7,4,3,4,2},
				 {10,3,13,4,10},
				 {10,10,3,4,10},
				 {11,15,15,7,14},
				 {8,8,8,8,9}};
int i, j;
int **laberintoBin;



int inicializarMatrices(){
	//laberinto		= (int **)malloc(g_filas*sizeof(int *));
	laberintoBin	= (int **)malloc((g_filas*3)*sizeof(int *));
	
	//for (i = 0; i < g_filas; i++)
		//laberinto[i]	= (int *)malloc(g_columnas*sizeof(int));
	for (i = 0; i < g_filas*3; i++)
		laberintoBin[i]	= (int *)malloc((g_columnas*3)*sizeof(int));
	
	//for (i = 0; i < g_filas; i++)
      	//for (j = 0; j < g_columnas; j++)
			//laberinto[i][j] = 0;
	for (i = 0; i < g_filas*3; i++)
      	for (j = 0; j < g_columnas*3; j++)
			laberintoBin[i][j] = 0;
	
	return 1;
}

int conversion_aux(int k, int l){
	switch(laberinto[k][l]){
		case 1:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 2:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 3:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 4:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 5:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 6:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 7:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 0; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 8:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 9:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 10:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 11:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 0; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 12:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 13:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 0; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 14:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 0;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
		case 15:
			laberintoBin[k*3][l*3] = 0; laberintoBin[k*3][(l*3)+1] = 1; laberintoBin[k*3][(l*3)+2] = 0;
			laberintoBin[(k*3)+1][l*3] = 1; laberintoBin[(k*3)+1][(l*3)+1] = 1; laberintoBin[(k*3)+1][(l*3)+2] = 1;
			laberintoBin[(k*3)+2][l*3] = 0; laberintoBin[(k*3)+2][(l*3)+1] = 1; laberintoBin[(k*3)+2][(l*3)+2] = 0;
			break;
	}
	return 1;
}

int conversion(){
	for (i = 0; i < g_filas; i++)
 		for (j = 0; j < g_columnas; j++)
			conversion_aux(i, j);
	return 1;
}




bool tremaux(int row, int col) {

  if(laberintoBin[row][col] == 0 || laberintoBin[row][col] == 8){
    return false;
  }
  if(row == ((g_filas*3)-2) && col == ((g_columnas*3)-1)){
    return true;
  }
  laberintoBin[row][col] = 8;
  if (tremaux(row-1, col))
    return true;

  if (tremaux(row, col+1))
    return true;

  if (tremaux(row+1, col))
    return true;

  if (tremaux(row, col-1))
    return true;

  laberintoBin[row][col] = 1;
  
  return false;
}


bool verifica_raton(int x, int y){
    if(x >= 0 && x < g_columnas && y >= 0 && y < g_filas && laberintoBin[x][y] == 1)
        return true;
    return false;
}
 

bool raton(int x, int y){

    if(x == g_columnas-1 && y == g_filas-1)
    {
        laberintoBin[x][y] = 1;
        return true;
    }
 
    if(verifica_raton(x, y) == true)
    {
        laberintoBin[x][y] = 8;
 
        if (raton(x+1, y) == true)
            return true;

        if (raton(x, y+1) == true)
            return true;

        laberintoBin[x][y] = 0;
        return false;
    }   
 
    return false;
}






int main(int argc, char **argv)
{
	inicializarMatrices();
    
    
	conversion();
	
	for (i = 0; i < g_filas; i++){
 		for (j = 0; j < g_columnas; j++)
			printf("%d\t", laberinto[i][j]);
		printf("\n");
    }
	printf("\n");
	
	for (i = 0; i < g_filas*3; i++){
		if(i%3 == 0 && i > 1)
			printf("------|-------|-------|-------|------\n");
 		for (j = 0; j < g_columnas*3; j++){
			if(j%3 == 0 && j > 1)
				printf("| ");
			printf("%d ", laberintoBin[i][j]);
		}
		printf("\n");
    }
	
    
    printf("\n");
    printf("\n");
    
    
    
    //OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO OJO 
    
    
    //tremaux(1, 0);
    
    raton(0, 0);
    
    
    


	for (i = 0; i < g_filas*3; i++){
		if(i%3 == 0 && i > 1)
			printf("------|-------|-------|-------|------\n");
 		for (j = 0; j < g_columnas*3; j++){
			if(j%3 == 0 && j > 1)
				printf("| ");
			printf("%d ", laberintoBin[i][j]);
		}
		printf("\n");
    }
    
    
    
    
	return 0;
}


#include <stdio.h>
#include <stdlib.h>

int g_columnas 	= 5;
int g_filas 	= 5;

int laberinto [5][5] = {{7,4,3,4,2},
				 {10,3,13,4,10},
				 {10,10,3,4,10},
				 {11,15,15,7,14},
				 {8,8,8,8,9}};
int i, j;
//int **laberinto;
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
	
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int g_columnas 	= 5;
int g_filas 	= 5;

int laberinto [5][5] = {
                 {7,4,3,4,2},
				 {10,3,13,4,10},
				 {10,10,3,4,10},
				 {11,15,15,7,14},
				 {8,8,8,8,9}
};


int spanningTree [5][5] = {
                 {7,4,3,4,2},
				 {10,3,13,4,10},
				 {10,10,3,4,10},
				 {11,15,15,7,14},
				 {8,8,8,8,9}
};



int resultado [5][5];
int resultadoDerecha[5][5];
int resultadoIzquierda[5][5];
int resultadopledge[5][5];
int resultadoraton[5][5];

int i, j;
int **laberintoBin;

int ruta[100][2];
int pos_ruta;

int inicializarMatrices(){
	laberintoBin	= (int **)malloc((g_filas*3)*sizeof(int *));

	for (i = 0; i < g_filas*3; i++){
		laberintoBin[i]	= (int *)malloc((g_columnas*3)*sizeof(int));     
    }

	for (i = 0; i < g_filas*3; i++)
      	for (j = 0; j < g_columnas*3; j++){
			laberintoBin[i][j] = 0;
        }
	
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

int direccion = 0;

bool preguntaSur(int pNum){
	if((pNum == 2) || (pNum == 3) || (pNum == 6) || (pNum == 7) || (pNum == 10) || (pNum == 11) || (pNum == 14) || (pNum == 15)){
		return true;
	}
	return false;
}

bool preguntaEste(int pNum){
	if((pNum == 1) || (pNum == 3) || (pNum == 5) || (pNum == 7) || (pNum == 9) || (pNum == 11) || (pNum == 13) || (pNum == 15)){
		return true;
	}
	return false;
}

bool preguntaNorte(int pNum){
	if((pNum == 8) || (pNum == 9) || (pNum == 10) || (pNum == 11) || (pNum == 12) || (pNum == 13) || (pNum == 14) || (pNum == 15)){
		return true;
	}
	return false;
}

bool preguntaOeste(int pNum){
	if((pNum == 4) || (pNum == 5) || (pNum == 6) || (pNum == 7) || (pNum == 12) || (pNum == 13) || (pNum == 14) || (pNum == 15)){
		return true;
	}
	return false;
}



void raton() {
    int row = 0; 
    int col = 0;
  while(row != 4 && col != 4){
    printf("%d - %d\n",row,col);
    if (preguntaEste(laberinto[row-1][col])){
        //printf("ESTE\n");
        resultadoraton[row][col] = 1;
        row--;
    }
    if (preguntaOeste(laberinto[row][col+1])){
        //printf("Oeste\n");
        resultadoraton[row][col] = 1;
        col++;
    }
    if (preguntaSur(laberinto[row+1][col])){
        //printf("SUR\n");
        resultadoraton[row][col] = 1;
        row++;
    }
    if (preguntaNorte(laberinto[row][col-1])){
       // printf("NORTE\n");
        resultado[row][col] = 1;
        col--;
    }
        
    //resultado[row][col] = 0;
    row++;
    col++;
      
  }

}





void pledge(){
    int i=0,j=0,counter=0,k=0;
	spanningTree[0][0]-=4;
	while((i<g_filas-1) || (j<g_columnas-1)){
		if(counter!=0){
			if(counter%4==1){
				if(spanningTree[i][j]&1){
					counter--;
					j++;
                    printf("%d - %d\n",i,j);
                    resultadopledge[i][j] = 1; 
				}else if((spanningTree[i][j]>>1)&1){
					i++;
                    resultadopledge[i][j] = 1; 
				}else{
					counter++;
				}
			}else if(counter%4==0){
				if((spanningTree[i][j]>>3)&1){
					counter--;
					i--;
                    printf("%d - %d\n",i,j);
                     resultadopledge[i][j] = 1; 
				}else if(spanningTree[i][j]&1){
					j++;
                    resultadopledge[i][j] = 1; 
				}else{
					counter++;
				}
			}else if(counter%4==3){
				if((spanningTree[i][j]>>2)&1){
					counter--;
					j--;
                    printf("%d - %d\n",i,j);
                     resultadopledge[i][j] = 1; 
				}else if((spanningTree[i][j]>>3)&1){
					i--;
                    resultadopledge[i][j] = 1; 
				}else{
					counter++;
				}
			}else{
				if((spanningTree[i][j]>>1)&1){
					counter--;
					i++;
                    printf("%d - %d\n",i,j);
                     resultadopledge[i][j] = 1; 
				}else if((spanningTree[i][j]>>2)&1){
					j--;
                    resultadopledge[i][j] = 1; 
				}else{
					counter++;
				}
			}
		}else{
			if(!(spanningTree[i][j]&1)){
				counter++;
                printf("%d - %d\n",i,j);
                 resultadopledge[i][j] = 1; 
			}else{
				j++;
			}
		}
		k++;
	}
	spanningTree[0][0]+=4;
}



void resuelveDerecha(){

	
	int pXInicio = 0;
	int pYInicio = 0;

    

	direccion = 0;
	int numPos = 0;

	resultadoDerecha[pXInicio][pYInicio] = 1;
	int i = 0;

	
	while(!(pXInicio == (g_columnas-1) && pYInicio == (g_filas-1))){ 
		i++;
		numPos = laberinto[pXInicio][pYInicio];
		
		if(direccion == 3){ //SI estamos caminando hacia el norte
			//printf("estoy en norte\n");
			if(preguntaEste(numPos)){
				pYInicio++;
				direccion = 0;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else if(preguntaNorte(numPos)){
				pXInicio--;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else{
				direccion = 2;
			}
		}else if(direccion == 2){ //SI estamos caminando hacia el oeste.
			//printf("estoy en oeste\n");
			if(preguntaNorte(numPos)){
				pXInicio--;
				direccion = 3;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else if(preguntaOeste(numPos)){
				pYInicio--;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else{
				direccion = 1;
			}
		}else if(direccion == 1){ //SI estamos caminando hacia el sur.
			//printf("estoy en sur\n");
			if(preguntaOeste(numPos)){
				pYInicio--;
				direccion = 2;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else if(preguntaSur(numPos)){
				pXInicio++;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else{
				direccion = 0;
			}
		}else if(direccion == 0){ //SI estamos caminando hacia el este.
			//printf("estoy en este\n");
			if(preguntaSur(numPos)){
				pXInicio++;
				direccion = 1;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else if(preguntaEste(numPos)){
				pYInicio++;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}else{
				direccion = 3;
			}
		}


	}

	printf("En total mire: %d\n", i);
}



void resuelveIzquierda(){

	
	int pXInicio = 0;
	int pYInicio = 0;

	direccion = 0;
	int numPos = 0;

	resultadoIzquierda[pXInicio][pYInicio] = 1;
	int i = 0;

	while(!(pXInicio == (g_columnas-1) && pYInicio == (g_filas-1))){ 
		i++;
		numPos = spanningTree[pXInicio][pYInicio];
		//printf("me quede pegado en x: %d y en la Y: %d \n", pXInicio, pYInicio);
		if(direccion == 3){ //SI estamos caminando hacia el norte
			//printf("estoy en norte\n");
			if(preguntaOeste(numPos)){
				pYInicio--;
				direccion = 2;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else if(preguntaNorte(numPos)){
				pXInicio--;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else{
				direccion = 1;
			}
		}else if(direccion == 2){ //SI estamos caminando hacia el oeste.
			//printf("estoy en oeste\n");
			if(preguntaSur(numPos)){
				pXInicio++;
				direccion = 1;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else if(preguntaOeste(numPos)){
				pYInicio--;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else{
				direccion = 0;
			}
		}else if(direccion == 1){ //SI estamos caminando hacia el sur.
			//printf("estoy en sur\n");
			if(preguntaEste(numPos)){
				pYInicio++;
				direccion = 0;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else if(preguntaSur(numPos)){
				pXInicio++;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else{
				direccion = 3;
			}
		}else if(direccion == 0){ //SI estamos caminando hacia el este.
			//printf("estoy en este\n");
			if(preguntaNorte(numPos)){
				pXInicio--;
				direccion = 3;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else if(preguntaEste(numPos)){
				pYInicio++;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}else{
				direccion = 2;
			}
		}


	}

	printf("En total mire: %d\n", i);
}





int main(int argc, char **argv)
{
	inicializarMatrices();
    
    
	//conversion();
	
	for (i = 0; i < g_filas; i++){
 		for (j = 0; j < g_columnas; j++)
			printf("%d\t", laberinto[i][j]);
		printf("\n");
    }
	printf("\n");
	
    /*
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
	*/
    
    printf("\n");
    printf("\n");
    
    

    raton();
    
    pledge();
    
    resuelveDerecha();
        
    resuelveIzquierda();    
     
    printf("\n");
    printf("\n");
    
    
    printf("RATON\n");
    
    for (i = 0; i < g_filas; i++){
 		for (j = 0; j < g_columnas; j++)
			printf("%d\t", resultadoraton[i][j]);
		printf("\n");
    }
	printf("\n");
    
    
    
    
    printf("PLEDGE\n");
    
    for (i = 0; i < g_filas; i++){
 		for (j = 0; j < g_columnas; j++)
			printf("%d\t", resultadopledge[i][j]);
		printf("\n");
    }
	printf("\n");
    
    
    printf("DERECHA\n");
    
    for (i = 0; i < g_filas; i++){
 		for (j = 0; j < g_columnas; j++)
			printf("%d\t", resultadoDerecha[i][j]);
		printf("\n");
    }
	printf("\n");
    
    printf("IZQUIERDA\n");

    
    for (i = 0; i < g_filas; i++){
 		for (j = 0; j < g_columnas; j++)
			printf("%d\t", resultadoIzquierda[i][j]);
		printf("\n");
    }   
    //conversion();
    
    
    
    
    
    
	return 0;
}


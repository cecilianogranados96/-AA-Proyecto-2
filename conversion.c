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

<<<<<<< HEAD





=======
>>>>>>> origin/master
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



<<<<<<< HEAD
int avanzar(int direccion, int direccionAnterior,int i, int j){
	if((direccionAnterior+=2)%4==direccion){
		return 0;
	}else if((direccion==0) && (laberinto[i][j]&1)){
		return 1;
	}else if((direccion==1) && ((laberinto[i][j]>>1)&1)){
		return 1;
	}else if((direccion==2) && ((laberinto[i][j]>>2)&1)){
		return 1;
	}else if((direccion==3) && ((laberinto[i][j]>>3)&1)){
		return 1;
	}
	return 0;
}

void raton(){
	int i=0,j=0,k=0,direccion=0,cambioDireccion,direccionRandom;
	laberinto[0][0]-=4;
	while((i<g_filas-1) || (j<g_columnas-1)){
		cambioDireccion=0;
		if(laberinto[i][j]==1){
			direccion=0;
		}else if(laberinto[i][j]==2){
			direccion=1;
		}else if(laberinto[i][j]==4){
			direccion=2;
		}else if(laberinto[i][j]==8){
			direccion=3;
		}else{
			while(!cambioDireccion){
				direccionRandom=rand()%4;
				if(avanzar(direccionRandom,direccion,i,j)){
					cambioDireccion=1;
					direccion=direccionRandom;
				}
			}
		}
		if(direccion==0){
			j++;
            resultadoraton[i][j] = 1; //OJO
		}else if(direccion==1){
			i++;
            resultadoraton[i][j] = 1; //OJO
		}else if(direccion==2){
			j--;
            resultadoraton[i][j] = 1; //OJO
		}else{
			i--;
            resultadoraton[i][j] = 1; //OJO
		}
		k++;
	}
	laberinto[0][0]+=4;
=======
bool avanzar(int direccion, int direccionAnterior,int i, int j){
	if((direccionAnterior += 2)%4 == direccion)
		return false;
	else if((direccion == 0) && (laberinto[i][j]&1))
		return true;
	else if((direccion == 1) && ((laberinto[i][j]>>1)&1))
		return true;
	else if((direccion == 2) && ((laberinto[i][j]>>2)&1))
		return true;
	else if((direccion == 3) && ((laberinto[i][j]>>3)&1))
		return true;
	return false;
}

void raton(){
	int pXInicio = 0, pYInicio = 0, numPos = 0, direccion = 0;
	int cambioDireccion, direccionRandom;
	laberinto[0][0] -= 4;
	
	while((pXInicio < g_filas-1) || (pYInicio < g_columnas-1)){
		cambioDireccion = 0;
		if(laberinto[pXInicio][pYInicio] == 1)
			direccion = 0;
		else if(laberinto[pXInicio][pYInicio] == 2)
			direccion = 1;
		else if(laberinto[pXInicio][pYInicio] == 4)
			direccion = 2;
		else if(laberinto[pXInicio][pYInicio] == 8)
			direccion = 3;
		else
			while(!cambioDireccion){
				direccionRandom = rand()%4;
				if(avanzar(direccionRandom,direccion,pXInicio,pYInicio)){
					cambioDireccion = 1;
					direccion = direccionRandom;
				}
			}
		if(direccion==0){
			pYInicio++;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		else if(direccion==1){
			pXInicio++;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		else if(direccion==2){
			pYInicio--;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		else{
			pXInicio--;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		numPos++;
	}
	laberinto[0][0] += 4;
>>>>>>> origin/master
}






void pledge(){
<<<<<<< HEAD
    int i=0,j=0,counter=0,k=0;
	laberinto[0][0]-=4;
	while((i<g_filas-1) || (j<g_columnas-1)){
		if(counter!=0){
			if(counter%4==1){
				if(laberinto[i][j]&1){
					counter--;
					j++;
                    resultadopledge[i][j] = 1; 
				}else if((laberinto[i][j]>>1)&1){
					i++;
                    resultadopledge[i][j] = 1; //OJO
				}else{
					counter++;
				}
			}else if(counter%4==0){
				if((laberinto[i][j]>>3)&1){
					counter--;
					i--;
                     resultadopledge[i][j] = 1; 
				}else if(laberinto[i][j]&1){
					j++;
                     resultadopledge[i][j] = 1; //OJO
				}else{
					counter++;
				}
			}else if(counter%4==3){
				if((laberinto[i][j]>>2)&1){
					counter--;
					j--;
                    
                      resultadopledge[i][j] = 1; //OJO
				}else if((laberinto[i][j]>>3)&1){
					i--;
                     resultadopledge[i][j] = 1; //OJO
				}else{
					counter++;
				}
			}else{
				if((laberinto[i][j]>>1)&1){
					counter--;
					i++;
                    
                    resultadopledge[i][j] = 1; //OJO
				}else if((laberinto[i][j]>>2)&1){
					j--;
                     resultadopledge[i][j] = 1; //OJO
				}else{
					counter++;
=======
    int pXInicio = 0, pYInicio = 0, pCounter = 0, numPos = 0;
	laberinto[0][0] -= 4;
	while((pXInicio < g_filas-1) || (pYInicio < g_columnas-1)){
		if(pCounter != 0){
			if(pCounter%4 == 1){
				if(laberinto[pXInicio][pYInicio]&1){
					pCounter--;
					pYInicio++;
                    resultadopledge[pXInicio][pYInicio]++; 
				}
				else if((laberinto[pXInicio][pYInicio]>>1)&1){
					pXInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
				}
				else
					pCounter++;
			}
			else if(pCounter%4 == 0){
				if((laberinto[pXInicio][pYInicio]>>3)&1){
					pCounter--;
					pXInicio--;
					resultadopledge[pXInicio][pYInicio]++; 
				}
				else if(laberinto[pXInicio][pYInicio]&1){
					pYInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
>>>>>>> origin/master
				}
				else
					pCounter++;
			}
<<<<<<< HEAD
		}else{
			if(!(laberinto[i][j]&1)){
				counter++;
                 resultadopledge[i][j] = 1; //OJO
			}else{
				j++;
                 resultadopledge[i][j] = 1; //OJO
=======
			else if(pCounter%4 == 3){
				if((laberinto[pXInicio][pYInicio]>>2)&1){
					pCounter--;
					pYInicio--;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
				}
				else if((laberinto[pXInicio][pYInicio]>>3)&1){
					pXInicio--;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
				}
				else
					pCounter++;
			}
			else{
				if((laberinto[pXInicio][pYInicio]>>1)&1){
					pCounter--;
					pXInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
				}
				else if((laberinto[pXInicio][pYInicio]>>2)&1){
					pYInicio--;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
				}
				else
					pCounter++;
>>>>>>> origin/master
			}
		}
		else{
			if(!(laberinto[pXInicio][pYInicio]&1)){
				pCounter++;
                resultadopledge[pXInicio][pYInicio]++; //OJO
			}
			else{
				pYInicio++;
                resultadopledge[pXInicio][pYInicio]++; //OJO
			}
		}
		numPos++;
	}
	laberinto[0][0]+=4;
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
		numPos = laberinto[pXInicio][pYInicio];
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


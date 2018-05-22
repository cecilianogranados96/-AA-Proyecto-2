#include <stdio.h>

int preguntaSur(int pNum){
	if((pNum == 2) || (pNum == 3) || (pNum == 6) || (pNum == 7) || (pNum == 10) || (pNum == 11) || (pNum == 14) || (pNum == 15))
		return 1;
	return 0;
}

int preguntaEste(int pNum){
	if((pNum == 1) || (pNum == 3) || (pNum == 5) || (pNum == 7) || (pNum == 9) || (pNum == 11) || (pNum == 13) || (pNum == 15))
		return 1;
	return 0;
}

int preguntaNorte(int pNum){
	if((pNum == 8) || (pNum == 9) || (pNum == 10) || (pNum == 11) || (pNum == 12) || (pNum == 13) || (pNum == 14) || (pNum == 15))
		return 1;
	return 0;
}

int preguntaOeste(int pNum){
	if((pNum == 4) || (pNum == 5) || (pNum == 6) || (pNum == 7) || (pNum == 12) || (pNum == 13) || (pNum == 14) || (pNum == 15))
		return 1;
	return 0;
}

void resuelveDerecha(){
	int pXInicio = xInicio, pYInicio = yInicio;
	int pXFinal = xFinal, pYFinal = yFinal;
	int numPos = 0, i = 0;
	
	resultadoDerecha[pXInicio][pYInicio] = 1;
	direccion = 0;
	
	printf("el num X es:%d y el num Y: %d\n", pXInicio, pYInicio);
	printf("Debemos igual la X = %d a la X %d, y la Y = %d a la Y = %d \n", pXInicio, pXFinal, pYInicio, pYFinal );
	
	while(!(pXInicio == pXFinal && pYInicio == pYFinal)){ //(pXInicio != pXFinal) && (pYInicio != pYFInal) i < 4
		i++;
		numPos = spanningTree[pXInicio][pYInicio];
		//printf("me quede pegado en x: %d y en la Y: %d \n", pXInicio, pYInicio);
		if(direccion == 3){ //SI estamos caminando hacia el norte
			//printf("estoy en norte\n");
			if(preguntaEste(numPos)){
				pYInicio++;
				direccion = 0;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else if(preguntaNorte(numPos)){
				pXInicio--;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 2;
		}
		else if(direccion == 2){ //SI estamos caminando hacia el oeste.
			//printf("estoy en oeste\n");
			if(preguntaNorte(numPos)){
				pXInicio--;
				direccion = 3;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else if(preguntaOeste(numPos)){
				pYInicio--;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 1;
		}
		else if(direccion == 1){ //SI estamos caminando hacia el sur.
			//printf("estoy en sur\n");
			if(preguntaOeste(numPos)){
				pYInicio--;
				direccion = 2;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else if(preguntaSur(numPos)){
				pXInicio++;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 0;
		}
		else if(direccion == 0){ //SI estamos caminando hacia el este.
			//printf("estoy en este\n");
			if(preguntaSur(numPos)){
				pXInicio++;
				direccion = 1;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else if(preguntaEste(numPos)){
				pYInicio++;
				resultadoDerecha[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 3;
		}
	}
	printf("En total mire: %d\n", i);
}

void resuelveIzquierda(){
	int pXInicio = xInicio, pYInicio = yInicio;
	int pXFinal = xFinal, pYFinal = yFinal;
	int numPos = 0, i = 0;
	
	resultadoIzquierda[pXInicio][pYInicio] = 1;
	direccion = 0;
	
	printf("el num X es:%d y el num Y: %d\n", pXInicio, pYInicio);
	printf("Debemos igual la X = %d a la X %d, y la Y = %d a la Y = %d \n", pXInicio, pXFinal, pYInicio, pYFinal );
	
	while(!(pXInicio == pXFinal && pYInicio == pYFinal)){ //(pXInicio != pXFinal) && (pYInicio != pYFInal) i < 4
		i++;
		numPos = spanningTree[pXInicio][pYInicio];
		//printf("me quede pegado en x: %d y en la Y: %d \n", pXInicio, pYInicio);
		if(direccion == 3){ //SI estamos caminando hacia el norte
			//printf("estoy en norte\n");
			if(preguntaOeste(numPos)){
				pYInicio--;
				direccion = 2;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else if(preguntaNorte(numPos)){
				pXInicio--;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 1;
		}
		else if(direccion == 2){ //SI estamos caminando hacia el oeste.
			//printf("estoy en oeste\n");
			if(preguntaSur(numPos)){
				pXInicio++;
				direccion = 1;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else if(preguntaOeste(numPos)){
				pYInicio--;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 0;
		}
		else if(direccion == 1){ //SI estamos caminando hacia el sur.
			//printf("estoy en sur\n");
			if(preguntaEste(numPos)){
				pYInicio++;
				direccion = 0;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else if(preguntaSur(numPos)){
				pXInicio++;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 3;
		}
		else if(direccion == 0){ //SI estamos caminando hacia el este.
			//printf("estoy en este\n");
			if(preguntaNorte(numPos)){
				pXInicio--;
				direccion = 3;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else if(preguntaEste(numPos)){
				pYInicio++;
				resultadoIzquierda[pXInicio][pYInicio] = 1;
			}
			else
				direccion = 2;
		}
	}
	printf("En total mire: %d\n", i);
}

int main(int argc, char **argv)
{
	
	return 0;
}


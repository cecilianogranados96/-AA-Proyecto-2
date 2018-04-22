#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rows,columns,**laberinto,**spanningTree,*frontierR,*frontierC,n=-1,counter=-1;

void addAdjacent(int rowIndex,int columnIndex){
	if(laberinto[rowIndex][columnIndex]==0){
		n++;
		laberinto[rowIndex][columnIndex]=-1;
		frontierR[n]=rowIndex;
		frontierC[n]=columnIndex;
	}
}

void markAdjacent(int rowIndex,int columnIndex){
	if(rowIndex!=0){
		addAdjacent(rowIndex-1,columnIndex);
	}
	if(rowIndex!=rows-1){
		addAdjacent(rowIndex+1,columnIndex);	
	}
	if(columnIndex!=0){
		addAdjacent(rowIndex,columnIndex-1);
	}
	if(columnIndex!=columns-1){
		addAdjacent(rowIndex,columnIndex+1);
	}
}

void isAdjacent(int indexR,int indexC,int adjacentR[],int adjacentC[]){
	if((laberinto[indexR][indexC]==1)||(laberinto[indexR][indexC]==16)){
		counter++;
		adjacentR[counter]=indexR;
		adjacentC[counter]=indexC;
	}
}

void asignConection(){
	int k,adjacentR[4],adjacentC[4],adjacentToConnect,frontierCellR,frontierCellC;
	if(n==0){
		k=0;
	}else{
		k=rand()%n;
	}
	frontierCellR=frontierR[k],frontierCellC=frontierC[k];
	counter=-1;
	if(frontierCellR!=0){
		isAdjacent(frontierCellR-1,frontierCellC,adjacentR,adjacentC);
	}
	if(frontierCellR!=rows-1){
		isAdjacent(frontierCellR+1,frontierC[k],adjacentR,adjacentC);	
	}
	if(frontierCellC!=0){
		isAdjacent(frontierCellR,frontierC[k]-1,adjacentR,adjacentC);
	}
	if(frontierCellC!=columns-1){
		isAdjacent(frontierCellR,frontierC[k]+1,adjacentR,adjacentC);
	}
	if(counter==0){
		adjacentToConnect=0;
	}else{
		adjacentToConnect=rand()%counter;
	}
	if(adjacentR[adjacentToConnect]==frontierCellR-1){
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=2;
		spanningTree[frontierCellR][frontierCellC]+=8;
	}else if(adjacentR[adjacentToConnect]==frontierCellR+1){
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=8;
		spanningTree[frontierCellR][frontierCellC]+=2;
	}else if(adjacentC[adjacentToConnect]==frontierCellC+1){
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]=4;
		spanningTree[frontierCellR][frontierCellC]+=1;
	} else{
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=1;
		spanningTree[frontierCellR][frontierCellC]+=4;
	}
	laberinto[frontierCellR][frontierCellC]=1;
	markAdjacent(frontierCellR,frontierCellC);
	frontierR[k]=frontierR[n];
	frontierC[k]=frontierC[n];
	n--;
}

void createMaze(){
	int i,j,randomR,randomC;
    rows 
        columns
	printf("Type the matrix rows: ");
  	scanf("%d", &rows);
  	printf("Type the matrix columns: ");
  	scanf("%d", &columns);
    
    
    
    
    
	frontierR=(int *)malloc(rows*columns*sizeof(int));
	frontierC=(int *)malloc(rows*columns*sizeof(int));
	spanningTree=(int **)malloc(rows*sizeof(int *));
	laberinto=(int **)malloc(rows*sizeof(int *));
	for (i = 0; i < rows; i++){
		laberinto[i]=(int *)malloc(columns*sizeof(int));
		spanningTree[i]=(int *)malloc(columns*sizeof(int));
	}
  	for (i = 0; i < rows; i++){
      		for (j = 0; j < columns; j++){
			laberinto[i][j]=0;
			spanningTree[i][j]=0;
		}
	}
	randomR=rand()%rows;
	randomC=rand()%columns;
	laberinto[randomR][randomC]=16;
	markAdjacent(randomR,randomC);
	asignConection();
	while(n!=-1){
		asignConection();
	}

	printf("expansion:\n");
	for (i = 0;i<rows;i++){
 		for (j = 0;j<columns;j++){
			printf("%d\t",spanningTree[i][j]);
		}
		printf("\n");
	}
    
    
	for(int i=0;i<rows;i++){
		free(laberinto[i]);
		free(spanningTree[i]);
	}
    

    
	free(laberinto);
	free(spanningTree);
	free(frontierR);
	free(frontierC);
	n=-1;
	counter=-1;
}

int main(){
	srand(time(NULL));
	createMaze();
	return 0;
}

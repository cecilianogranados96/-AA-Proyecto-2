#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Display the maze. */
void ShowMaze(const char *maze, int width, int height) {
   int x, y;
   for(y = 0; y < height; y++) {
      for(x = 0; x < width; x++) {
         switch(maze[y * width + x]) {
         case 1:  printf("[]");  break;
         case 2:  printf("<>");  break;
         default: printf("  ");  break;
         }
      }
      printf("\n");
   }
}


void CarveMaze(char *maze, int width, int height, int x, int y) {
   int x1, y1;
   int x2, y2;
   int dx, dy;
   int dir, count;
   dir = rand() % 4;
   count = 0;
   while(count < 4) {
      dx = 0; dy = 0;
      switch(dir) {
          case 0:  dx = 1;  break;
          case 1:  dy = 1;  break;
          case 2:  dx = -1; break;
          default: dy = -1; break;
      }
      x1 = x + dx;
      y1 = y + dy;
      x2 = x1 + dx;
      y2 = y1 + dy;
      if(   x2 > 0 && x2 < width && y2 > 0 && y2 < height && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
         maze[y1 * width + x1] = 0;
         maze[y2 * width + x2] = 0;
         x = x2; y = y2;
         dir = rand() % 4;
         count = 0;
      } else {
         dir = (dir + 1) % 4;
         count += 1;
      }
   }

}

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height) {

   int x, y;
   for(x = 0; x < width * height; x++) {
      maze[x] = 1;
   }
   maze[1 * width + 1] = 0;
   srand(time(0));
   for(y = 1; y < height; y += 2) {
      for(x = 1; x < width; x += 2) {
         CarveMaze(maze, width, height, x, y);
      }
   }
    
   maze[0 * width + 1] = 0;
   maze[(height - 1) * width + (width - 2)] = 0;

}


/*
void guardar (char nombre[1024]) {
 	int  i, j,c = 0;
 	char buffer[1024], cadena[1024];
 	FILE *archivo = fopen (nombre, "w+");
    
    for(i = 0; i < g_col; i++) {
        for(j = 0; j < g_fil; j++) {
         sprintf(buffer, "%d", maze[c]);
         strcat(cadena, buffer);
         c++;
        }
	}
    fwrite(cadena, sizeof(char), sizeof(cadena), archivo);
    fclose (archivo); 
    
    
    
}*/


int main(int argc,char *argv[]) {
    
   int width = 4; 
   int height = 4;
   char *maze;


   width = width * 2 + 3;
   height = height * 2 + 3;

   maze = (char*)malloc(width * height * sizeof(char));


   //GenerateMaze(maze, width, height);
   //ShowMaze(maze, width, height);

    
    
     char cadena1 [1024]; 
    FILE* fichero;
    fichero = fopen("guardar.txt", "rt");
    fgets (cadena1, 1024, fichero);     
    char * pch = strtok (cadena1," ,");
    int pos = 0;
        while (pch != NULL){
            maze[pos] = atoi(pch);
            printf("%d", atoi(pch));
            pch = strtok (NULL, " ,"); 
            pos++;
        }
    fclose(fichero);
    
    
    ShowMaze(maze, width, height);
    
    
    

   exit(EXIT_SUCCESS);

}
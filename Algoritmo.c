#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SpwTrR[4];
int SpwTrC[4];
int stp;
int Entry; 
int Exit;




void addFrontier(int m, int n,int i, int j,int ar[][n]){
    if (0<=i-1){
        if(ar[i-1][j]==0){
            SpwTrR[stp]=i-1;
            SpwTrC[stp]=j;
            ar[i-1][j]=-1;
            stp++;
        }
    }
    if (0<=j-1){
        if(ar[i][j-1]==0){
            SpwTrR[stp]=i;
            SpwTrC[stp]=j-1;
            ar[i][j-1]=-1;
            stp++;
        }
    }
    if (i+1<m){
        if(ar[i+1][j]==0){
            SpwTrR[stp]=i+1;
            SpwTrC[stp]=j;
            ar[i+1][j]=-1;
            stp++;
        }
    }
    if (j+1<n){
        if(ar[i][j+1]==0){
            SpwTrR[stp]=i;
            SpwTrC[stp]=j+1;
            ar[i][j+1]=-1;
            stp++;
        }
    }
}

void removeBarrier(int m, int n,int i, int j,int ar[][n]){
    int select=0;
    int pos[4]={0};
    int resp,temp;
    if (0<=i-1){
        if(ar[i-1][j]>0){
            pos[select]=4;
            select++;
        }
    }
    if (0<=j-1){
        if(ar[i][j-1]>0){
            pos[select]=3;
            select++;
        }
    }
    if (i+1<m){
        if(ar[i+1][j]>0){
            pos[select]=2;
            select++;
        }
    }
    if (j+1<n){
        if(ar[i][j+1]>0){
            pos[select]=1;
            select++;
        }
    }
    temp=rand()%select;
    resp=pos[temp];
    if (resp==1){
        ar[i][j+1]+=4;
        ar[i][j]=1;
    }
    else if (resp==2){
        ar[i+1][j]+=8;
        ar[i][j]=2;
    }
    else if (resp==3){
        ar[i][j-1]+=1;
        ar[i][j]=4;
    }
    else if (resp==4){
        ar[i-1][j]+=2;
        ar[i][j]=8;
    }
}

void setentrys(int m, int n,int ar[][n]){
    int ei,ej,si,sj,ig,p;
    ig=1;
    ei=ej=si=sj=0;
    if(m>1){
        ei=rand()% m;
        si=rand()% m;
    }
    if(n>1){
        ej=rand()% n;
        sj=rand()% n;
    }
    int pos[4]={0,ei,m-1,si};
    int alt[4]={ej,n-1,sj,0};
    p=rand()%4;
    ei=pos[p];
    ej=alt[p];
    if(n*m==1){
        int sel[4]={1,2,4,8};
        ej=sel[p];
        while (ig){
            p=rand()%4;
            sj=sel[p];
            if(ej!=sj)
                ig=0;
        }
        ar[0][0]=ej+sj;
    }else{
        while (ig){
            p=rand()%4;
            si=pos[p];
            sj=alt[p];
            if(ei*n+ej!=si*n+sj)
                ig=0;
        }
        Entry=ei*n+ej;//variables para interfaz
        Exit=si*n+sj;//variables para interfaz
        if (ej==n-1){
            ar[ei][ej]+=1;
        }
        else if (ei==m-1){
            ar[ei][ej]+=2;
        }
        else if (ej==0){
            ar[ei][ej]+=4;
        }
        else if (ei==0){
            ar[ei][ej]+=8;
        }

        if (sj==n-1){
            ar[si][sj]+=1;
        }
        else if (si==m-1){
            ar[si][sj]+=2;
        }
        else if (sj==0){
            ar[si][sj]+=4;
        }
        else if (si==0){
            ar[si][sj]+=8;
        }
    }
}

int resolv(int m,int n,int ar[][n]){
    int spawn = rand() % (n*m);
    int mov;
    int i,j;
    stp=0;
    Entry=Exit=0;
    for(i=0;i<m;i++){//reiniciar la matriz para interfaz
        for(j=0;j<n;j++)
            ar[i][j]=0; 
    }
    if(n*m>1){
		i=spawn/n;
		j=spawn%n;
		ar[i][j]=16;
		addFrontier(m,n,i,j,ar);
		while(stp>0){
			mov=0;
			if(stp>0)
				mov = rand()%stp;
			i=SpwTrR[mov];
			j=SpwTrC[mov];
			SpwTrR[mov]=SpwTrR[stp-1];
			SpwTrC[mov]=SpwTrC[stp-1];
			stp--;
			removeBarrier(m,n,i,j,ar);
			addFrontier(m,n,i,j,ar);
		}
		i=spawn/n;
		j=spawn%n;
		ar[i][j]-=16;
	}
    setentrys(m,n,ar);
    return 1;
}


int main(int argc,char *argv[]) {
    
   int width = 4; 
   int height = 4;
    int ar[width][height];
    resolv(width,height,ar);
    
    
    for(int x = 0; x < 4; x += 1){
		for(int y = 0; y < 4; y += 1){
			 printf("%d \t",ar[x][y]);
		}
        printf("\n");
	}
    
    


}
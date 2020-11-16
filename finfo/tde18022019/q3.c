#include <stdio.h>
#include <stdlib.h>

#define NROW 7
#define NCOL 10

void myf(int[][NCOL],int,int,int,int*,int*);

int main(int argc,char * argv[]){
	int matr[NROW][NCOL],num,i,j,x,y;
	num=45;

	for (i=0;i<NROW;i++)
		for(j=0;j<NCOL;j++)
			matr[i][j]=i+j;
	
	myf(matr,NROW,NCOL,num,&x,&y);

	printf("numero ha coordinate %d %d\n",x,y);
	
	return 0;
}

void myf(int mat[][NCOL],int nr,int nc,int val, int*cx, int*cy){
	int i,j,somma;
	somma=0;
	for(i=0;i<nr;i++)
		for(j=0;j<nc;j++){
			somma+=mat[i][j];
			if(somma>val){
				*cx=i;
				*cy=j;
				return;
			}
			}
	*cx=-1;
	*cy=-1;
	return;
	}


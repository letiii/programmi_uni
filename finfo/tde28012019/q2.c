#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5

typedef struct point_s{
	int x;
	int y;
}point_t;

int regolare(point_t[][N],int);
float dist(point_t,point_t);

int main(int argc,char * argv[]){
	point_t mat[N][N];
	int i,j,reg;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++){
			mat[i][j].x=i+j;
			mat[i][j].y=i+j;
			}
	reg=regolare(mat,N);
	printf("%d\n",reg);
	return 0;
}

float dist(point_t p1,point_t p2){
	float d;
	d = sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
	return d;
	}

int regolare(point_t m[][N],int dim){
	int i,j,flag;
	float r,c,diag;
	
	flag=1;
	diag=0;
	for(i=0;i<dim-1;i++)
		for(j=0;j<dim-1;j++)
			if(i==j)
				diag+=dist(m[i][j],m[i+1][j+1]);

	for(i=0;i<dim && flag;i++){
		r=0;
		c=0;
		for(j=0;j<dim-1;j++){
			r+=dist(m[i][j],m[i][j+1]);
			c+=dist(m[j][i],m[j+1][i]);
			}
		if(r>diag || c>diag)
			flag=0;
			}
		return flag;
			}

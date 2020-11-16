#include <stdio.h>

int main (int argc, char * argv[]){
int a,b,mcd,aux,mcm,r;
scanf("%d  %d",&a,&b);
mcd=a;
aux=b;
while(aux!=0){
	r=mcd%aux;
	mcd=aux;
	aux=r;
}
mcm=(a*b)/mcd;
printf("mcd e' %d mcm e' %d\n",mcd,mcm);
return 0;
}

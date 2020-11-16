#include <stdio.h>
#include <stdlib.h>
#define STOP -1
#define BASE 10

int conta(FILE *);

int main(int argc, char * argv[]){
	FILE * fp;
	int ris;
	if(fp=fopen("dati.txt","r")){
		ris=conta(fp);
		while(ris!=STOP){
			printf("%d\n",ris);
			ris=conta(fp);
			}
		fclose(fp);
	}else
		printf("errore apertura file");
	return 0;
}


int conta(FILE* fp){
	int cont[BASE],i,n,max;
	for(i=0;i<BASE;i++)
		cont[i]=0;
	fscanf(fp,"%d",&n);
	if(!feof(fp)){
		while(n>0){
			cont[n%BASE]++;
			n/=BASE;
		}
		max=0;
		for(i=1;i<BASE;i++)
			if(cont[i]>=cont[max])
				max=i;
	}else
		max=-1;
	return max;
}

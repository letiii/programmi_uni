#include <stdio.h>
#define D 5
int main(int argc, char * argv[]){
	int cont,k,k1,j,i1[D],i2[D],i,u[D*2],in[D];
/*acquisisco elementi di entrambi gli insiemi*/
	for(i=0;i<D;i++)
		scanf("%d",&i1[i]);
	for(i=0;i<D;i++)	
		scanf("%d",&i2[i]);
/*inizializzo contatori vari*/
	cont=0;
	k=0;
	k1=0;
/*calcolo insieme di unione*/
	for(i=0;i<D;i++)
		u[i]=i1[i];
	for(i=0;i<D;i++){
		for(j=0;j<D;j++)
			if(i2[i]!=i1[j])
				cont++;
		if(cont==D){
			u[k+D]=i2[i];
			k++;
		}
		cont=0;
	}
/*calcolo insieme itersezione*/
	for(i=0;i<D;i++)
		for(j=0;j<D;j++)
			if(i1[i]==i2[j]){
				in[k1]=i1[i];
				k1++;
			}
/*stampo insiemi di unione e intersezione*/
	for(i=0;i<k+D;i++)
		printf("%d ",u[i]);
	printf("\n");
	for(i=0;i<k1;i++)
		printf("%d ",in[i]);
	printf("\n");	
	return 0;
}


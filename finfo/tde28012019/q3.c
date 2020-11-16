#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define BASE 2
#define J 'x'
void genera(char []);

int main(int argc,char * argv[]){
	char * s;
	s=argv[1];
	genera(s);
	return 0;
}


void genera(char s[]){
	int dim,i,c,j,comb,k;
	dim=strlen(s);
	for(i=0,c=0;i<dim;i++)
		if(s[i]==J)
			c++;
	comb=pow(BASE,c);
	for(i=0;i<comb;i++){
		for(j=0,k=i;j<dim;j++)
			if(s[j]==J){
				printf("%d",k%2);
				k/=2;
			}else
				printf("%c",s[j]);
		printf("\n");
	}
	return;
}

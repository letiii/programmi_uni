#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FNAME "dizionario.txt"
#define LMAX 25
#define USED '1'
#define NOTUSED '0'
#define BASE 10
int anagramma(char[], char[]);
int dimmianagrammi(int);
char * int2str(int);

int main(int argc,char * argv[]){
	char parola[LMAX];
	strcpy(parola,"9981");
	printf("%d\n",dimmianagrammi(atoi(parola)));
	return 0;
}

int anagramma(char s1[], char s2[]){
	char * s;
	int l,i,j,found;

	l=strlen(s1);
	if(l!=strlen(s2))
		return 0;
	if(s=(char*)malloc(sizeof(char)*l)){
		for(i=0;i<l;i++)
			s[i]=NOTUSED;
		for(i=0;i<l;i++){
			for(j=0,found=0;j<l && !found; j++)
				if(s1[i]==s2[j] && s[j]==NOTUSED){
					s[j]=USED;
					found=1;
				}
			if(!found)
				return 0;
			
		}
		free(s);
		return 1;
	}
	printf("problema di memoria: %d\n",l+1);
	return 0;
}

int dimmianagrammi(int val){
	FILE * fp;
	char voc[LMAX+1];
	char * nums;
	int dim,n;
	
	n=-1;

	if(fp=fopen(FNAME,"r")){
		n=0;
		nums=int2str(val);
		dim=strlen(nums);

		fscanf(fp,"%s",voc);
		while(!feof(fp)){
			if(dim==strlen(voc) &&strcmp(nums,voc))
				if(anagramma(nums,voc)){
					printf("%s\n",voc);
					n++;
				}
			fscanf(fp,"%s",voc);
					}
		fclose(fp);

	}
	else
		printf("problema di accesso al %s", FNAME);
	return n;
}

char * int2str(int n){
	int ncifre,dup,i;
	char * ns;
	dup=n;
	ncifre=0;
	while(dup>0){
		dup=dup/BASE;
		ncifre++;
	}
	if(ncifre==0)
		ncifre++;
	if(ns=(char*)malloc(sizeof(char)*(ncifre+1))){
		*(ns+ncifre)='/0';
		for(i=ncifre-1;i>=0;i--){
			*(ns+i)=n%BASE+'0';
			n=n/BASE;
		}
	}
	else
		printf("problema di memoria %d",n);
	return ns;
}

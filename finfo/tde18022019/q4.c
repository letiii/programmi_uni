#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FNAME "dizionario.txt"
#define LMAX 25
#define USED '1'
#define NOTUSED '0'

int anagramma(char[], char[]);
int dimmianagrammi(char[]);

int main(int argc,char * argv[]){
	char parola[LMAX];
	strcpy(parola,"mira");
	printf("%d\n",dimmianagrammi(parola));
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

int dimmianagrammi(char s[]){
	FILE * fp;
	char voc[LMAX+1];
	int l,n;
	
	n=-1;

	if(fp=fopen(FNAME,"r")){
		n=0;
		l=strlen(s);

		fscanf(fp,"%s",voc);
		while(!feof(fp)){
			if(l==strlen(voc) &&strcmp(s,voc))
				if(anagramma(s,voc)){
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

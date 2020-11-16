#include <stdio.h>
#include <stdlib.h>
#define FN "/home/studente/Desktop/file_prova_1"
#define N 20


int main(int argc,char * argv[]){
	FILE * fin;
	char s[N];
	if(fin=fopen(FN,"w")){
		fprintf(fin,"%s","ciao, ");
		fprintf(fin,"%s","dolci verdi non sono per niente gay");
		fprintf(fin,"%s","\n e quelli tra dolci verdi che dicono di essere gay, veranno spalmati di ketchup\n");
		fclose(fin);		
	}
	else 
		fprintf(stdout,"errore di apertura %s",FN);
	if(fin = fopen(FN, "r")){
		fgets(s,N,fin);
		printf("%s",s);
		fclose(fin);
	}
	return 0;
}

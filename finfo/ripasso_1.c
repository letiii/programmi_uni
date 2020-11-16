#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define N 3
#define NS 2

typedef struct date_s{
	int d,m,y;
}date_t;

typedef struct studente_s{
	char cognome[MAX+1],nome [MAX+1];
	date_t birth;
	int voti[N];
	float media;

}studente_t;

void enter(studente_t [],int );
void acvoti(studente_t[],int ,int [],int);
void media(studente_t[],int);

int main (int argc, char * argv[]){
	int x;
	studente_t studenti[NS];
	enter(studenti,NS);
	for(x=0;x<NS;x++)
		acvoti(studenti,x,studenti[x].voti,N);
	for(x=0;x<NS;x++)
		media(studenti,x);
	return 0;
		}

void enter(studente_t studenti[], int dim){
	int i;
	for(i=0;i<dim;i++){
		printf("inserire il nome dello studente numero %d\n",(i+1));
		scanf("%s",studenti[i].nome);
		printf("inserire il cognome dello studente numero %d\n", (i+1));
		scanf("%s", studenti[i].cognome);
		printf("inserire data di nascita gg mm aaaa\n");
		scanf("%d %d %d",&studenti[i].birth.d,&studenti[i].birth.m,&studenti[i].birth.y);
	}
}


void acvoti(studente_t studenti[],int x, int voti[],int dim){
	int i;
	for(i=0;i<dim;i++){ 
		printf("inserire il voto numero %d (in trentesimi) dello studente %s %s\n",(i+1),studenti[x].cognome,studenti[x].nome);
		scanf("%d",&studenti[x].voti[i]);		
	}

}


void media (studente_t studenti[],int x){
	int i,tot=0;
	for(i=0;i<N;i++)
		tot=tot+studenti[x].voti[i];
	studenti[x].media=(float)tot/N;
	printf("la media di %s %s e' %.1f\n",studenti[x].cognome,studenti[x].nome,studenti[x].media);

}

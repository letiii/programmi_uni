#include <stdio.h>
#include <stdlib.h>

#define BASE 10

typedef struct nodo_s{
	int val;
	struct nodo_s * next;
}nodo_t;

nodo_t * int2list(int);
nodo_t *  push(nodo_t *,int);
nodo_t * append(nodo_t *,int);

int main(int argc,char * argv[]){
	
	int num;
	nodo_t * lista=NULL;
	nodo_t * aux;
	num = atoi(argv[1]);
	lista=int2list(num);
	for(aux=lista;aux;aux=aux->next)
		printf("%d\t",aux->val);
	printf("\n");
	return 0;
}

nodo_t * int2list(int x){
	int r,i,neg;
	nodo_t * h = NULL;
	neg=0;
	if(x<0){
		neg=1;
		x=-x;
	}
	if(neg){
		while(x>0){
			r=x%BASE;
			for(i=0;i<r;i++)
				h=append(h,r);
			x=x/BASE;
		}
	}
	else{
		while(x>0){
			r=x%BASE;
			for(i=0;i<r;i++)
				h=push(h,r);
			x=x/BASE;

		}
	}
	return h;
}

nodo_t * push(nodo_t * h, int n){
	nodo_t * e;
	if((e=(nodo_t *)malloc(sizeof(nodo_t)))){
		e->val =n;
		e->next =h;
		h=e;
	}
	else
		printf("errore nell'allocazione memoria nella funzione push\n");
	return h;
}

nodo_t * append(nodo_t * h, int n){
	nodo_t * e, *ptr;
	if((e=(nodo_t*)malloc(sizeof(nodo_t)))){
		e->val =n;
		e->next =	NULL;
		if(!h)
			h=e;
		else{
			for(ptr=h;ptr->next; ptr =ptr->next)
				;
			ptr->next =e;
		}
	}
	else
		printf("errore nell'allocazione memoria nella funzione append\n");
	return h;
}

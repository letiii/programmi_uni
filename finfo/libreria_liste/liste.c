#include "/home/studente/Desktop/liste.h"
#include <stdio.h>
#include <stdlib.h>


/*funzioni*/
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


nodo_t * inverte(nodo_t * h){
	nodo_t * inv = NULL;
	nodo_t * ptr;
	for(ptr=h;ptr;ptr=ptr->next)
		inv=push(inv,ptr->val);
	freelist(h);
	return inv;
}


nodo_t * pushNoAlloc(nodo_t * h, nodo_t * e){
	e->next=h;
	return e;
}


void freelist(nodo_t * h){
	nodo_t * temp;
	while(h){
		temp=h;
		h=h->next;
		free(temp);
	}
	return;
}

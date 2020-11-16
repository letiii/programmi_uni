/*tipo di dati per le  liste*/
typedef struct nodo_s{
	int val;
	struct nodo_s * next;
}nodo_t;


/*prototipi funzioni*/
nodo_t * append(nodo_t *, int);    /*insersce l'elemento in coda alla lista*/
nodo_t * push(nodo_t *, int);    /*inserisce l'elemeto in testa alla lista*/
nodo_t * inverte(nodo_t *);    /*restituisce una lista nuova con elementi in ordine inverso*/
nodo_t * pushNoAlloc(nodo_t *, nodo_t *);    /*inserisce l'elemeto in testa alla lista senza allocare memoria nuova*/
void freelist(nodo_t *);    /*elimina la lista, rilasciando la memoria*/ 
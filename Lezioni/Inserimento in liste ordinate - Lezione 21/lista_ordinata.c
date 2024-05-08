#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct nodolista{
	
	int dato;
	
	//puntatore al nodo sucessivo
	struct nodolista *next;
}nodo;

void termina(const char messaggio []);

nodo *crea_nodo(int n);

void stampa_lista(nodo *lis,FILE *pFile);

nodo *inserimento_ordinato(nodo *lis,nodo *z);

nodo *inserimento_ordinato_ric(nodo *lis,nodo *z);

int main(int argc,char *argv[]){
	
	if(argc<2)
		termina("Uso: x1 x2 x3 .... xn\n");

  nodo *lis = NULL;
  for(int i=1;i<argc;i++) {
    
    int valore = atoi(argv[i]);
    nodo *el = crea_nodo(valore);
    
    //lis = inserimento_ordinato(lis,el);
    lis = inserimento_ordinato_ric(lis,el);
    
    stampa_lista(lis,stdout);
  }
  
  puts("================");
  
  stampa_lista(lis,stdout);
  
  return 0;
}

nodo *inserimento_ordinato(nodo *lis,nodo *z){

	if(lis==NULL){
		z->next = NULL;
		return z;
	}	
	
	if(z->dato<=lis->dato){
		z->next = lis;
		return z;
	}

	nodo *prec = lis;
	nodo *el = lis->next;
	while(el != NULL){
		if(z->dato<el->dato){
			z->next = el;
			prec->next = z;
			return lis;
		}
		prec = el;
		el = el->next;
	}
	
	prec->next = z;
	z->next = NULL;
	
	return lis;
}

nodo *inserimento_ordinato_ric(nodo *lis,nodo *z){

	if(lis==NULL){
		z->next = NULL;
		return z;
	}
		
	if(z->dato<lis->dato){
		z->next = lis;
		return z;
	}
	
	nodo *tmp = inserimento_ordinato_ric(lis->next,z);
	
	lis->next = tmp;
	return lis;
}

nodo *crea_nodo(int numero){
	
	nodo *n = malloc(sizeof(nodo));
	
	if(n==NULL)
		termina("Errore malloc");
		
	n->dato = numero;
	n->next = NULL;
	
	return n;
}

void stampa_lista(nodo *lis,FILE *pFile){
	
	nodo *el = lis;
	while(el != NULL){
		fprintf(pFile,"%d\t",el->dato);
		el = el->next;
	}
	fprintf(pFile,"\n");

	return;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

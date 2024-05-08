#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

//definito il tipo nodo che al suo interno contiene due campi
typedef struct nodolista{
	
	int dato;
	
	//puntatore al nodo sucessivo
	struct nodolista *next;
}nodo;

void termina(const char messaggio []);

nodo *crea_nodo(int n);

nodo *cancella_elemento(nodo *lis,int elemento_da_cancellare);

void stampa_lista(nodo *lis,FILE *pFile);

nodo *inserisci_elemento_dopo_valore(nodo *lis,int inserisci_dato,int inserisci_dopo);

void dealloca_lista(nodo *lis);

/*
 Aggiungere al programma lista_indel.c una funzione lis *cancella_ultimo(nodo *lis) 
 che data una lista cancella il suo ultimo elemento; 
 la funzione deve restituire il puntatore al primo elemento della lista modificata. 
 Verificare che il metodo funzioni correttamente anche quando la lista data in input è vuota o contiene un singolo 
 elemento (in entrambi i casi deve essere restituita la lista vuota) 
*/

nodo *cancella_ultimo(nodo *lis); 

int main(int argc, char *argv[]){

	//richiede almeno un argomento sulla linea di comando.
	if(argc<2)
		termina("Uso: x1 x2 x3 ... xn");
	
	nodo *lis = NULL;
	for(int i = argc-1;i>=1;i--){
		//aggiunge un elemento in cima alla lista 
		nodo *el = crea_nodo(atoi(argv[i]));
		el->next = lis;
		lis = el;
	}
	
	fprintf(stdout,"--- Stampa Lista ---\n");
	stampa_lista(lis,stdout);
	fprintf(stdout,"--- Fine Lista ---\n");
	
	inserisci_elemento_dopo_valore(lis,2,7);
	
	fprintf(stdout,"--- Inserisci il 2 dopo il 7 ---\n");
	stampa_lista(lis,stdout);
	fprintf(stdout,"--- Fine Lista ---\n");
	
	lis = cancella_elemento(lis,10);
	
	fprintf(stdout,"--- Cancella elemento 10 ---\n");
	stampa_lista(lis,stdout);
	fprintf(stdout,"--- Fine Lista ---\n");
	
	lis = cancella_elemento(lis,1);
	
	fprintf(stdout,"--- Cancella elemento 1 ---\n");
	stampa_lista(lis,stdout);
	fprintf(stdout,"--- Fine Lista ---\n");
	
	lis = cancella_ultimo(lis);
	
	fprintf(stdout,"--- Cancella ultimo elemento ---\n");
	stampa_lista(lis,stdout);
	fprintf(stdout,"--- Fine Lista ---\n");
	
	dealloca_lista(lis);
	
	return 0;
}

nodo *cancella_ultimo(nodo *lis){

	if(lis == NULL)
		return lis;
	else if(lis->next == NULL){
		free(lis);
		return NULL;
	}
	
	nodo *aprec = lis;
	nodo *bprec = lis->next;
	nodo *el = lis->next->next;
	while(el != NULL){
		aprec = bprec; 
		bprec = el;
		el = el->next;
	}
	
	aprec->next = NULL;
	free(bprec);
	
	return lis;
}

//data una lista, inserisco un elemento della lista e lo inserisco dopo il valore "inserisci_dopo"
nodo *inserisci_elemento_dopo_valore(nodo *lis,int inserisci_dato,int inserisci_dopo){

	assert(lis != NULL);
	
	nodo *el = lis;
	while(el != NULL){
		if(el->dato == inserisci_dopo){
			
			nodo *newEl = crea_nodo(inserisci_dato);
			
			newEl->next = el->next;
			el->next = newEl;
			
			return lis;
		}
		el = el->next;
	}
	
	return lis;
}

nodo *cancella_elemento(nodo *lis,int elemento_da_cancellare){
	
	//andiamo a vedere se la lista è vuota o no!
	if(lis == NULL) return lis;
	
	if(lis->dato == elemento_da_cancellare){
		
		nodo *tmp = lis->next;
		free(lis);
		return tmp;
	}
	
	//punta al primo elemento della lista(esiste e lo sappiamo grazie al controllo di riga 88)
	nodo *prec = lis;
	nodo *el = lis->next;
	
	while(el != NULL){
		
		assert(prec->next == el);
		
		if(el->dato == elemento_da_cancellare){
			
			prec->next = el->next;
			free(el);
			
			return lis;
		}
		prec = el;
		el = el->next;
	}
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

void dealloca_lista(nodo *lis){
		
	nodo *el = lis;
	while(el!=NULL){
		nodo *tmp = el->next;
		free(el);
		el = tmp;
	}
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

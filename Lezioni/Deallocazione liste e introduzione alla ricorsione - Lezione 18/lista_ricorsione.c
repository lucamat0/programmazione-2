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

/*
Definire le funzioni:
-Stampa Lista
-Conta elementi Lista
-Somma totale degli elementi della lista

->Le seguenti funzioni devono "lavorare" ricorsivamente. 
*/
void stampa_lista(nodo *lis,FILE *pFile);

int conta_elementi(nodo *lis);

int somma_elementi(nodo *lis);

/*

1) Aggiungere al programma lista_ricorsione.c una funzione ricorsiva int max_lista(nodo *lis) 
* che data una lista di interi non vuota restituisce il massimo dei suo elementi. 
* La strategia da seguire è la seguente: Se la lista ha un solo elemento allora quello è il massimo, 
* se la lista ha più di un elemento il massimo è il più grande tra il primo elemento e il massimo degli 
* elementi dal secondo in poi.

2) Aggiungere al programma lista_ricorsione.c una funzione void stampa_ribaltata(nodo *lis) che data una 
* lista di interi stampa i suoi elementi in ordine inverso, cioè dall'ultimo al primo. 
* La strategia da seguire è la seguente: se la lista è vuota non stampo nulla, se c'e' almeno un elemento 
* allora eseguo la stampa ribaltata degli elementi dal secondo in poi seguita dalla stampa del primo elemento. 
* Osserviamo infatti che se la lista contiene gli elementi 2 5 7 1 8 9 se eseguo la stampa ribaltata 
* di 5 7 1 8 9 ottengo 9 8 1 7 5 che seguita dalla stampa di 2 produce 9 8 1 7 5 2 cioè la stampa ribaltata 
* della lista di partenza. Si provi anche ad eseguire la stampa ribaltata senza usare la ricorsione.

*/

int max_lista(nodo *lis);
void stampa_ribaltata(nodo *lis);

int main(int argc, char *argv[]){

	//richiede almeno un argomento sulla linea di comando.
	if(argc<2)
		termina("Uso: x1 x2 x3 ... xn");
	
	nodo *lis = NULL;
	for(int i = 1;i<argc;i++){
		//aggiunge un elemento in cima alla lista 
		nodo *el = crea_nodo(atoi(argv[i]));
		el->next = lis;
		lis = el;
	}
	
	stampa_lista(lis,stdout);
	
	fprintf(stdout,"Il numero di elementi e': %d\n",conta_elementi(lis));
	fprintf(stdout,"La somma totale degli elementi e': %d\n",somma_elementi(lis));
	fprintf(stdout,"L'elemento massimo che si trova all'interno della lista e': %d\n",max_lista(lis));
	
	stampa_ribaltata(lis);
	fprintf(stdout,"\n");
	
	return 0;
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
	
	if(lis==NULL){
		fprintf(pFile,"\n--- Fine Lista ---\n");
		return;
	}
	
	fprintf(pFile,"%d\t",lis->dato);
	
	stampa_lista(lis->next,pFile);
	
	return;
}	

int conta_elementi(nodo *lis){
	
	if(lis==NULL)
		return 0;
	
	return 1+conta_elementi(lis->next);
}

int somma_elementi(nodo *lis){
		
	if(lis==NULL)
		return 0;
	
	return lis->dato+somma_elementi(lis->next);
}

int max_lista(nodo *lis){
	
	if(lis->next==NULL)
		return lis->dato;
		
	int max_tmp = max_lista(lis->next);
	
	if(lis->dato>max_tmp)
		return lis->dato;
	else
		return max_tmp;
}

void stampa_ribaltata(nodo *lis){

	if(lis==NULL)
		return;
	
	stampa_ribaltata(lis->next);
	
	fprintf(stdout,"%d\t",lis->dato);
	
	return;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


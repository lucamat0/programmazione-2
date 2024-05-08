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

void stampa_lista(nodo *lis,FILE *pFile);

/*
Aggiungere al programma lista.c una funzione int conta_elementi(nodo *lis) che data una lista restituisce 
il numero in essa contenuti, e una funzione int somma_elementi(nodo *lis) che data una lista restituisce 
la somma degli interi in essa contenuti.
*/

int conta_elementi(nodo *lis);
int somma_elementi(nodo *lis);

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
	
	return 0;
}

int conta_elementi(nodo *lis){

	int conta = 0;
	
	nodo *el = lis;
	while(el != NULL){
		conta++;
		el = el->next;
	}
	
	return conta;
}

int somma_elementi(nodo *lis){

	int somma = 0;
	
	nodo *el = lis;
	while(el != NULL){
		somma += el->dato;
		el = el->next;
	}
	
	return somma;
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

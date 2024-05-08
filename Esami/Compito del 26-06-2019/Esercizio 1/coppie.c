#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

#include "coppie.h"

// crea una coppia contenente i valori x e y
coppia *crea_coppia(int x, int y){

	coppia *c = malloc(sizeof(coppia));
	
	if(c==NULL)
		termina("Errore malloc");
	
	c->primo = x;
	c->secondo = y;
	c->next = NULL;
	
	return c;
}

// inserisce l'elemento el in cima alla lista lis
coppia *inserisci_coppia(coppia *lis, coppia *el){

	assert(el!=NULL);
	
	if(lis==NULL)
		return el;
	
	el->next = lis;
	return el;
}

// legge 2 interi dal file binario f (8 byte in totale) e crea una coppia 
// con i valori corrispondenti chiamando la funzione crea_coppia() 
// restituisce NULL se non e' possibile leggere i due interi dal file f
coppia *crea_coppia_bin(FILE *f){

	assert(f!=NULL);
	
	int a;
	if(fread(&a,sizeof(int),1,f)!=1)
		return NULL;
	
	int b;
	if(fread(&b,sizeof(int),1,f)!=1)
		return NULL;
	
	coppia *el = crea_coppia(a,b);
	
	return el;	
}
// crea una lista con tutti gli interi presenti nel file
// il cui nome e' nomefile. Si supponga che gli interi
// siano memorizzati nel file in formato binario e che quindi
// devono essere letti con crea_coppie_bin().
// L'ordine con cui le coppie appaiono nel file non e' importante
// se non e' possibile leggere dal file la funzione deve
// restituire la lista vuota
coppia *crea_lista(char *nomefile){
		
	FILE *pFile = fopen(nomefile,"rb");
	
	if(pFile==NULL)
		termina("Errore fopen");
	
	coppia *lis = NULL;
	coppia *el;
	while((el = crea_coppia_bin(pFile))!=NULL){
		lis = inserisci_coppia(lis,el);
	}
	
	fclose(pFile);
	
	return lis;
}

// stampa sul file f gli interi della coppia el separati da uno spazio
void stampa_coppia(FILE *f, coppia *el){

	assert(el!=NULL);
	assert(f!=NULL);
	
	fprintf(f,"%d %d\t",el->primo,el->secondo);
}

// stampa sul file f tutte le coppie di lis separate da \n
// questa funzione *deve* utilizzare stampa_coppia() 
void stampa_lista_coppie(FILE *f, coppia *lis){

	assert(f!=NULL);
	
	if(lis==NULL)
		return;
	
	stampa_coppia(f,lis);
	
	stampa_lista_coppie(f,lis->next);
	
	return;
}

// restituisce un puntatore alla coppia della lista lis 
// la cui somma delle componenti (primo+secondo) ha valore massimo
// se ci sono più coppie con la stessa somma delle componenti
// restituire quella più lontana dalla testa della lista.  
coppia *cerca_coppia_maxsomma(coppia *lis){
		
	assert(lis!=NULL);
	
	int val_max = lis->primo+lis->secondo;
	coppia *coppia_max = lis;
	
	coppia *el = lis->next;
	while(el!=NULL){
		if((el->primo+el->secondo)>val_max){
			val_max = el->primo+el->secondo;
			coppia_max = el;
		}
		el = el->next;
	}
	return coppia_max;
}

// restituisce un puntatore alla prima coppia della lista lis 
// per cui la funzione f applicata ai campi primo e secondo 
// restituisce true. Se non esiste una tale coppia la funzione
// deve restituire NULL. 
coppia *cerca_coppia(coppia *lis, bool (*f)(int, int)){
	
	assert(lis!=NULL);
	
	coppia *el = lis;
	while(el!=NULL){
		if(f(el->primo,el->secondo)){
			return el;
		}
		el = el->next;
	}
	return NULL;
}

// dealloca tutti gli elementi della lista lis
void distruggi_lista_coppie(coppia *lis){

	if(lis==NULL)
		return;
	
	distruggi_lista_coppie(lis->next);
	
	free(lis);
	
	return;
}

/*
1b) Scrivere una funzione

coppia *duplica_lista(coppia *lis, bool (*f)(int, int))
che data una lista di coppie lis crea una nuova lista di coppie 
(senza modificare lis) contenente  una copia di tutte le coppie per cui
la funzione f restituisce true. Ad esempio se lis contiene le 
coppie (1,2) (5,-1) (2,-3) (4,4) (8,2) (-1,-1) la funzione duplica_lista
con secondo argomento la funzione positivi() definita sopra deve 
restituire una nuova lista contenente (1,2) (4,4) (8,2).
*/

coppia *duplica_lista(coppia *lis, bool (*f)(int, int)){

	assert(lis!=NULL);
	
	coppia *newLis = NULL;
	coppia *el = lis;
	while(el!=NULL){
		if(f(el->primo,el->secondo)==true){
			coppia *ell = crea_coppia(el->primo,el->secondo);
			newLis = inserisci_coppia_coda(newLis,ell);
		}
		el = el->next;
	}
	
	
	return newLis;

}

coppia *inserisci_coppia_coda(coppia *lis,coppia *el){

	if(lis==NULL){
		el->next = NULL;
		return el;
	}
	
	lis->next = inserisci_coppia_coda(lis->next,el);
	
	return lis;
}



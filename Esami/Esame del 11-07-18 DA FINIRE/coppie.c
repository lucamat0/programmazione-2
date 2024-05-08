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
	
	el->next = lis;
	return el;
}

// stampa sul file f gli interi della coppia el separati da uno spazio
void stampa_coppia(FILE *f, coppia *el){

	fprintf(f,"%d %d\n",el->primo,el->secondo);
}

// stampa sul file f tutte le coppie di lis separate da \n
// questa funzione *deve* utilizzare stampa_coppia() 
void stampa_lista_coppie(FILE *f, coppia *lis){

	if(lis==NULL)
		return;
		
	stampa_coppia(f,lis);
	
	stampa_lista_coppie(f,lis->next);
}

// restituisce la prima coppia della lista lis la cui somma è s
coppia *cerca_coppia(coppia *lis, int s){
	
	assert(lis!=NULL);
	
	coppia *el = lis;
	while(el!=NULL){
		if(el->primo+el->secondo==s)
			return el;
		else
			el = el->next;
	}
	return NULL;
}

// stampa sul file f tutte le coppie di lis la cui somma e' s
// questa funzione deve utilizzare cerca_coppia() e stampa_coppia()
void cerca_e_stampa_coppie(FILE *f, coppia *lis, int s){

	assert(f!=NULL);
	assert(lis!=NULL);
	
	coppia *el = lis;
	while((el = cerca_coppia(el,s))!=NULL){
		stampa_coppia(f,el);
		el = el->next;
	}
}

// restituisce il numero di coppie i cui elementi passati a f() restituiscono true
int conta_coppie(coppia *lis, bool (*f)(int, int)){

	if(lis==NULL)
		return 0;
	
	if(f(lis->primo,lis->secondo))
		return 1+conta_coppie(lis->next,f);
	else
		return 0+conta_coppie(lis->next,f);
}

// dealloca tutti gli elementi della lista lis
void distruggi_lista_coppie(coppia *lis){
	
	if(lis==NULL)
		return;
	
	distruggi_lista_coppie(lis->next);
	
	free(lis);
	return;
}

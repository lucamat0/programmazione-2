#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

#include <ctype.h>

#include "stringhe.h"

// crea una un elemento di tipo stringa contenente una copia di *s
// per duplicare un array di caratteri usare strdup()
stringa *crea_stringa(char *s){
		
	stringa *s1 = malloc(sizeof(stringa));
	
	if(s1==NULL)
		termina("Errore malloc");
		
	s1->s = strdup(s);
	s1->next = NULL;
	
	return s1;
}

// inserisce l'elemento el in testa alla lista lis
stringa *inserisci(stringa *lis, stringa *el){

	if(lis==NULL)
		return el;
	
	el->next = lis;
	lis = el;
	
	return lis;
}

// stampa sul file f la stringa in el, 
void stampa_stringa(FILE *f, stringa *el, bool reverse){
	
	if(!reverse)
		fprintf(f,"%s\n",el->s);
	else{
		for(int i=(strlen(el->s)-1);i>=0;i--)
			fprintf(f,"%c",el->s[i]);
		fprintf(f,"\n");
	}
	
	return;
}

// stampa sul file f tutte le stringhe di lis separate da \n
// questa funzione *deve* utilizzare stampa_stringa()
void stampa_lista(FILE *f, stringa *lis){

	if(lis==NULL)
		return;
	
	stampa_stringa(f,lis,false);
	
	stampa_lista(f,lis->next);
}

// dealloca tutti gli elementi della lista lis
// e anche tutti gli array di caratteri a cui questi elementi puntano
void distruggi_lista(stringa *lis){

	if(lis==NULL)
		return;
	
	distruggi_lista(lis->next);
	
	free(lis->s);
	free(lis);
	
	return;
}

stringa *duplica_se_pari(stringa *lis, int (*fun)(char *)){

	assert(lis!=NULL);
	
	if(fun(lis->s)%2==0){
		
		stringa *tmp = crea_stringa(lis->s);
		tmp->next = lis;
		
		if(lis->next != NULL){
			stringa *s = duplica_se_pari(lis->next,fun);
			lis->next = s;
		}
		
		return tmp;
	}
	
	stringa *prec = lis;
	stringa *el = lis->next;
	while(el!=NULL){
		
		if(fun(el->s)%2==0){
			
			stringa *tmp = crea_stringa(el->s);
			tmp->next = el;
			prec->next = tmp;		
		}
		prec = el;
		el = el->next;
	}
	
	return lis;
	
}

int conta_caratteri(char s[]){
	return strlen(s);
}

stringa *leggi_file_testo(FILE *pFile){

	char *s = NULL;
	size_t dim = 0;
	
	int e = getline(&s,&dim,pFile);
	
	if(e==-1){
		free(s);
		return NULL;
	}
	
	if(s[strlen(s)-1]=='\n')
		s[strlen(s)-1] = '\0';
	
	stringa *el = crea_stringa(s);
	free(s);
	
	return el;
}

stringa *gestisci_lettura_file_testo(FILE *pFile){

	stringa *lis = NULL;
	stringa *el;
	
	while((el = leggi_file_testo(pFile))!=NULL){
		
		el = leggi_file_testo(pFile);
		lis = inserisci(lis,el);
	
	}

	return lis;
}

int conta_maiuscole(char *s){
	
	int conta= 0;
	for(int i=0;i<=strlen(s);i++){
		if(isupper(s[i])!=0)
			conta++;
	}
	return conta;
}

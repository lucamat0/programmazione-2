#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

/*
2a) Si consideri la struct

typedef struct par {
  char *stringa;
  struct par *next; 
} parola;
che permette di rappresentare una lista di stringhe. 

Scrivere una funzione:

parola *delete_if(parola *lis, bool (*fun)(char *))
che data una lista di stringhe lis e una funzione fun 
cancella dalla lista lis tutti gli elementi contenenti 
stringhe per cui la funzione fun vale true. 
La funzione delete_if deve restituire il primo elemento della 
nuova lista o NULL se tutti gli elementi della lista vengono 
cancellati. 

Ad esempio data la funzione

bool lunghezza_pari(char *s) {
  return strlen(s)%2==0;
}

se lis contiene le stringhe "sole", "mare", "amore", "sale" 
l'invocazione

delete_if(lis, lunghezza_pari)

deve restituire la lista contenente solamente la stringa "amore". 
Si noti che quando si cancella un elemento di una lista si deve 
cancellare tutta la memoria da esso utilizzato

Per risolvere l'esercizio si consiglia di basarsi sulla seguente 
strategia ricorsiva:

if(fun(lis->stringa)) { // elemento da eliminare
  newlis = delete_if(lis->next,fun);
  cancella l'elemento a cui punta lis;
  return newlis; 
}

else { // elemento da tenere
  lis->next = delete_if(lis->next,fun);
  return lis;
}

*/

typedef struct par {
  char *stringa;
  struct par *next; 
} parola;

parola *delete_if(parola *lis, bool (*fun)(char *));

bool lunghezza_pari(char *s) {
  return strlen(s)%2==0;
}

parola *crea_elemento(char s[]);

void stampa_lista(parola *lis,FILE *pFile);
/*
2b) Si scriva un main che crea una lista lis contenente una copia
delle stringhe argv[1], argv[2], ..., argv[argc-1]
(in quest'ordine) e invoca delete_if passandogli come argomento 
lis e lunghezza_pari e stampa gli elementi della lista 
risultante. 
Dopo la stampa la lista deve essere completamente deallocata.
*/

void dealloca_lista(parola *lis);

int main(int argc,char *argv[]){
	
	if(argc==1)
		termina("Uso: string1 string2 ... stringN");
	
	parola *lis = NULL;
	parola *el;
	for(int i=(argc-1);i>0;i--){
		el = crea_elemento(argv[i]);
		el->next = lis;
		lis = el;
	}
	
	stampa_lista(lis,stdout);
	fprintf(stdout,"\n");
	
	lis = delete_if(lis,lunghezza_pari);
	
	stampa_lista(lis,stdout);
	fprintf(stdout,"\n");
	
	dealloca_lista(lis);
	
	return 0;
}

void dealloca_lista(parola *lis){
	
	if(lis==NULL)
		return;
	dealloca_lista(lis->next);
	
	free(lis->stringa);
	free(lis);
	
	return;
}

parola *delete_if(parola *lis, bool (*fun)(char *)){
	
	assert(lis!=NULL);
	
	if(fun(lis->stringa)){
		
		parola *tmp = lis->next;
		free(lis->stringa);
		free(lis);
		
		if(tmp!=NULL)
			lis = delete_if(tmp,fun);
		return lis;
	}
	
	parola *prec = lis;
	parola *el = lis->next;
	while(el!=NULL){
		if(fun(el->stringa)){
			prec->next = el->next;
			free(el->stringa);
			free(el);
			el = prec->next;
		}
		else{
			prec = el;
			el = el->next;
		}
	}
	return lis;	
}

void stampa_lista(parola *lis,FILE *pFile){

	if(lis==NULL)
		return;
		
	fprintf(pFile,"%s\t",lis->stringa);
	
	stampa_lista(lis->next,pFile);
	
	return;
}

parola *crea_elemento(char s[]){
	
	parola *p = malloc(sizeof(parola));
	
	if(p==NULL)
		termina("Errore malloc");
	
	p->stringa = strdup(s);
	p->next = NULL;
	
	return p;
}

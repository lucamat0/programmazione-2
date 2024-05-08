#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

#include <ctype.h>		//libreria che mi consente di utillizzare la funzione isupper

#include "stringhe.h"

void termina(const char messaggio[]);

/*
1a) Si consideri la struct

typedef struct str {
  char *s;
  struct str *next; 
} stringa;
che permette di rappresentare una lista di stringhe.

Scrivere un file stringhe.c, e il relativo stringhe.h, contenente le seguenti funzioni. 
Nel seguito lis è utilizzata per indicare una variabile che rappresenta una lista di 
stringhe (che puo' essere vuota), mentre el indica una variabile che punta ad una 
singola stringa.

// crea una un elemento di tipo stringa contenente una copia di *s
// per duplicare un array di caratteri usare strdup()
stringa *crea_stringa(char *s)

// inserisce l'elemento el in testa alla lista lis
stringa *inserisci(stringa *lis, stringa *el)

// stampa sul file f la stringa in el, 
void stampa_stringa(FILE *f, stringa *el, bool reverse)

// stampa sul file f tutte le stringhe di lis separate da \n
// questa funzione *deve* utilizzare stampa_stringa()
void stampa_lista(FILE *f, stringa *lis)

// dealloca tutti gli elementi della lista lis
// e anche tutti gli array di caratteri a cui questi elementi puntano
void distruggi_lista(stringa *lis)

1b) Si scriva una funzione:

stringa *duplica_se_pari(stringa *lis, int (*fun)(char *))

che data una lista di stringhe lis e una funzione fun che prende in input 
un array di caratteri e restituisce un intero, duplica tutti gli elementi della 
lista per cui la funzione fun restituisce un intero pari. La funzione deve resituire 
il puntatore al primo elemento della lista modificata. 
Ad esempio, se la lista contiene le stringhe

casa
aaa
 7yx yyy

le cui lunghezze rispettive sono 4, 3, e 8, invocando la funzione duplica_se passando questa lista e la funzione strlen devono essere 
duplicati il primo e il terzo elemento della lista. Di conseguenza al termine dell'esecuzione della funzione la lista deve 
contenere le stringhe

casa
casa
aaa
 7yx yyy
 7yx yyy
Si noti che duplicare un elemento significa anche duplicare la sequenza di caratteri in esso contenuto. 
La funzione deve restituire il puntatore al primo elemento della lista modificata.

1a) Si consideri la struct che permette di rappresentare una lista di stringhe.
Scrivere un file stringhe.c, e il relativo stringhe.h, contenente le seguenti funzioni. 
Nel seguito lis è utilizzata per indicare una variabile che rappresenta una lista di stringhe 
(che puo' essere vuota), mentre el indica una variabile che punta ad una singola stringa.
*/

int main(int argc,char *argv[]){
	
	if(argc!=3)
		termina("Uso: nome_del_file nome_file_risultato");
	
	FILE *pFile1 = fopen(argv[1],"rt");
	
	if(pFile1==NULL)
		termina("Errore fopen");
	
	stringa *lis = leggi_file_testo(pFile1);
	
	fclose(pFile1);
	
	stampa_lista(stdout,lis);
	
	lis = duplica_se_pari(lis,conta_maiuscole);
	
	stampa_lista(stdout,lis);
	
	FILE *pFile2 = fopen(argv[2],"wt");
	
	if(pFile2==NULL)
		termina("Errore fopen");
		
	stampa_lista(pFile2,lis);
	stampa_lista(stdout,lis);
	
	fclose(pFile2);
	
	return 0;
	
}


void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

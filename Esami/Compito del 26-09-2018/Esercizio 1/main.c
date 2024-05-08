/*
1a) Si utilizzi la struttura

typedef struct el {
  int val;
  struct el *next;
} intero;
per rappresentare un elemento di una lista di interi. 
Scrivere una funzione

intero *crea_lista(int n)
che dato un intero positivo n crea una lista contenente n interi uguali 
a 10, 20, 30, etc fino al valore n*10. 
Ad esempio, se n==8 la lista restituita deve contenere i valori 
(10,20,30,40,50,60,70,80) in quest'ordine.
*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct el{
  int val;
  struct el *next;
}intero;

intero *crea_lista(int n);

/*
1b) Scrivere una funzione

intero *inserisci(intero *lis, int val, int pos)

che inserisce l'intero val all'interno della lista lis secondo 
la seguente regola: se pos==0 l'intero va inserito in fondo alla lista; 
se pos==1 l'intero va inserito immediatamente prima dell'ultimo elemento; se pos==2 l'intero va inserito immediatamente prima del penultimo elemento e così via. Si noti che se pos è maggiore o uguale del numero di elementi della lista il valore val va inserito in cima alla lista.

*/
intero *inserisci(intero *lis, int val, int pos);
intero *inserisci_in_coda(intero *lis,intero *el);

/*
1c) Scrivere una funzione

void lista2bin(intero* lis, FILE *f)

scrive nel file f gli interi della lista lis in formato binario 
(quindi usando 4 byte per ogni intero) utilizzando la funzione fwrite.

*/
void lista2bin(intero* lis, FILE *f);

/*
1d) Scrivere un main che converte in intero il parametro argv[1] 
verifica che sia positiva e lo passa alla funzione crea_lista 
ottenendo così una lista lis di argv[1] interi. 
Successivamente main deve invocare:

lis = inserisci(lis,3,0);
lis = inserisci(lis,4,1);

e infine scrivere il nuovo contenuto di lis nel file di nome argv[2] 
utilizzando la funzione lista2bin. 
Prima di concludere main deve deallocare tutta la memoria utilizzata 
(verificare con valgrind).

*/
void dealloca_lista(intero *lis);

void termina(const char messaggio[]);
void stampa_lista(intero *lis);

int main(int argc,char *argv[]){
	
	if(argc != 3)
		termina("Uso: intero_positivo_maggiore_di_zero nome_file");
	
	int numero = atoi(argv[1]);
	
	if(numero<=0)
		termina("Il numero passato al eseguibile deve essere maggiore di zero");
	
	assert(numero>=1);
	
	intero *lis = NULL;
	for(int i = numero;i>=1;i--){
		intero *el = crea_lista(i*10);
		el->next = lis;
		lis = el;
	}

	stampa_lista(lis);
	fprintf(stdout,"\n");
	
	lis = inserisci(lis,3,0);
	lis = inserisci(lis,4,1);
	
	stampa_lista(lis);
	fprintf(stdout,"\n");
	
	FILE *pFile = fopen(argv[2],"wb");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	lista2bin(lis,pFile);
	
	dealloca_lista(lis);
	
	fclose(pFile);
	
	return 0;
}

void dealloca_lista(intero *lis){
	
	if(lis==NULL)
		return;
	
	dealloca_lista(lis->next);
	free(lis);
	return;
}

void lista2bin(intero* lis, FILE *f){
	
	intero *el = lis;
	while(el!=NULL){
		
		fwrite(&el->val,sizeof(int),1,f);
		el = el->next;
	}
}

intero *crea_lista(int n){

	assert(n>=1);
	
	intero *i = malloc(sizeof(intero));
	
	if(i==NULL)
		termina("Errore malloc");
	
	i->val = n;
	i->next = NULL;
	
	return i;
}

intero *inserisci(intero *lis, int val, int pos){

	intero *el = crea_lista(val);
	
	//l'intero va inserito al fondo della lista
	if(pos==0)
		lis = inserisci_in_coda(lis,el);
	//l'intero va inserito in cima alla lista
	else if(pos==1){
		el->next = lis;
		lis = el;
	}
	return lis;
}

intero *inserisci_in_coda(intero *lis,intero *el){

	if(lis->next == NULL){
		lis->next = el;
		el->next = NULL;
		return lis;
	}
	
	intero *i = inserisci_in_coda(lis->next,el);
	
	lis->next = i;
	
	return lis;
}

void stampa_lista(intero *lis){
	
	if(lis == NULL)
		return;
	
	fprintf(stdout,"%d \t",lis->val);
	
	stampa_lista(lis->next);
	return;
}

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}


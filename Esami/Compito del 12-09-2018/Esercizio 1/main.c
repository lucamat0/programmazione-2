/*
1a) Si scriva una funzione

int *stringa2array(char *s, int *n)
che data una stringa s contenente numeri interi separati da spazio crea 
e restituisce un array di int contenente gli interi presenti nella 
stringa. La funzione deve restituire il puntatore all'array creato e 
memorizzare in n il numero dei suoi elementi. 
Ad esempio, l'invocazione:

a = stringa2array(strdup("123 -5 34 40"),&n);
deve assegnare ad a l'array {123,-5,34,40} e alla variabile n il valore 4.
Si consiglia di usare le funzioni di libreria strtok per dividere 
la stringa s in token e atoi per convertire i singoli token in interi
*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

int *stringa2array(char *s, int *n);

void stampa_array(int *a,int dim,FILE *pFile);

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}
/*
1b) Si utilizzi la struttura

typedef strict el {
  int *a;
  int len;
  struct el *next;
} array;
per rappresentare un elemento di una lista di array di interi. 
Si scriva una funzione

array *file2lista(FILE *f);
che legge una linea alla volta dal file f (usare getline o fgets), 
passa le linee lette alla funzione stringa2array e restituisce la 
lista contenenti tali array. 
Ad esempio, se il file contiene le righe

-23 -5 11 34 
23 11 -2
1 1 1 1 1 11

la funzione deve restituire una lista di 3 elementi, 
in cui il primo elemento contiene l'array {-23, -5, 11, 34}, 
il secondo elemento l'array {23, 11, -2}, 
e il terzo elemento l'array {1,1,1,1,1,11} 
(ripettate l'ordine degli elementi).
*/

typedef struct el {
  int *a;
  int len;
  struct el *next;
}array;

array *crea_elemento(int *a,int dim);
array *file2lista(FILE *pFile);
array *crea_lista_array(FILE *pFile);
array *inserisci_in_coda(array *lis,array *el);

void stampa_lista(array *lis,FILE *pFile);

/*
1c) Scrivere una funzione

int somma_tutto(array *lis)
che data una lista di array lis esegue la somma di tutti gli interi 
contenuti negli array nella lista lis. 
Nell'esempio precedente, il valore resituito dalla funzione dovrebbe 
essere:

-23 -5 +11 +34 +23 +11 -2 +1 +1 +1 +1 +1 +11  = 65
*/
int somma_tutto(array *lis);

/*
1d) Scrivere un main che legge il nome di un file dalla linea di comando,
invoca su di esso la funzione file2lista e sulla lista ottenuta la 
funzione somma_tutto. 
Al termine deve deallocare tutta la memoria utilizzata per lista e 
array (verificare con valgrind).
*/
void dealloca_lista(array *lis);

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: nome_file_interi");
	/*
	//numero di elementi che si trovano all'interno dell'array a
	char *s = strdup("123 -5 34 40");
	
	int dim;
	int *a = stringa2array(s,&dim);
	
	assert(dim>0);
	
	stampa_array(a,dim,stdout);
	*/
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile==NULL)
		termina("Errore fopen");
	
	array *lis = crea_lista_array(pFile);
	fclose(pFile);
	
	stampa_lista(lis,stdout);
	
	int somma = somma_tutto(lis);
	
	fprintf(stdout,"Somma: %d\n",somma);
	
	dealloca_lista(lis);
	
	return 0;
}

void dealloca_lista(array *lis){
	if(lis==NULL)
		return;
		
	dealloca_lista(lis->next);
	
	free(lis->a);
	free(lis);
	
	return;
}

int somma_tutto(array *lis){
	
	int somma = 0;
	
	array *el = lis;
	while(el != NULL){
		for(int i = 0;i<el->len;i++){
			somma += el->a[i];
		}
		el = el->next;
	}
	
	return somma;
}

void stampa_lista(array *lis,FILE *pFile){
	
	if(lis==NULL)
		return;
		
	stampa_array(lis->a,lis->len,pFile);
	
	stampa_lista(lis->next,pFile);
	
	return;
}

array *inserisci_in_coda(array *lis,array *el){

	if(lis==NULL)
		return el;
	
	lis->next = inserisci_in_coda(lis->next,el);
	
	return lis;
}

array *crea_lista_array(FILE *pFile){
	
	array *lis = NULL;
	array *el;
	while((el = file2lista(pFile))!=NULL){
		lis = inserisci_in_coda(lis,el);
	}
	
	return lis;
}

array *file2lista(FILE *pFile){
	
	char *riga = NULL;
	size_t dimr = 0;
	
	int e = getline(&riga,&dimr,pFile);
	
	if(e==-1){
		free(riga);
		return NULL;
	}
	
	int dim;
	int *a = stringa2array(riga,&dim);
	
	array *el = crea_elemento(a,dim);
	
	free(riga);
	
	return el; 
}

array *crea_elemento(int *a,int dim){

	array *arr = malloc(sizeof(array));
	
	if(arr==NULL)
		termina("Errore malloc");
	
	arr->a = a;
	arr->len = dim;
	arr->next = NULL;
	
	return arr;
}

void stampa_array(int *a,int dim,FILE *pFile){
		
	for(int i = 0;i<dim;i++)
		fprintf(pFile,"%d\t",a[i]);
	fprintf(pFile,"\n");
}

int *stringa2array(char s[],int *dim){
	
	int size = 2;
	int messi = 0;
	int *a = malloc(sizeof(int)*size);
	
	if(a==NULL)
		termina("Errore malloc");
	
	char *t = strtok(s," ");
	
	a[0] = atoi(t);
	messi++;
	
	while((t = strtok(NULL," ")) != NULL){
		if(messi==size){
			size *= 2;
			a = realloc(a,sizeof(int)*size);
			
			if(a==NULL)
				termina("Errore realloc");
		}
	
		a[messi] = atoi(t);
		messi++;
	}
	
	size = messi;
	
	a = realloc(a,sizeof(int)*size);
	
	if(a==NULL)
		termina("Errore realloc");
	
	*dim = size;
	return a;
}

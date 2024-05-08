#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]);
void stampa_array(int *a,int dim);

/*
funzione che prende in input due puntatori a interi da confrontare
e restituisce:
	-1 se il primo va prima del secondo nell'ordinamento
	1 se il primo va dopo il secondo
	0 se il primo e il secondo sono equivalmentti rispetto all'ordinamento
i puntatori sono const perche' la funzione non ha il permesso di modificare
i valori a cui puntano a e b
*/
int confronta_interi(const int *n1,const int *n2);

int main(int argc,char *argv[]){
	
	if(argc<2)
		termina("Uso: x1 x2 ... xn");
	
	int dim = argc-1;
	int *a = malloc(sizeof(int)*dim);
	
	if(a==NULL)
		termina("Errore malloc");
		
	for(int i = 0;i<dim;i++)
		a[i] = atoi(argv[i+1]);
	
	stampa_array(a,dim);

	//eseguo il sorting degli interi.
	//(__compar_fn_t)confronta_interi -> ho eseguito il casting
	//"considera la funzione con il tipo che ti ho messo tra parentesi."
	//con questa tecnica sono in grado di silenziare il warming
	//l'operazione di cast sono da utilizzare con molta attenzione.
	qsort(a,dim,sizeof(int),(__compar_fn_t)confronta_interi);
/*
	qsort(void *a,int n,int size,int (*f)(void *,void *))
	la funzione f, segue la convenzione che dati due elementi
	qualunque essi siano devono restituire un intero che sara':
	->minore di 1 se il primo elemento e' piu' piccolo del secondo
	->maggiore di 1 se il secondo elemento e' piu' grande del secondo 
	->uguale a 0 se i due elementi sono uguali
	
	qsort = quick sort, e' un algoritmo veloce.
*/
	stampa_array(a,dim);
	
	return 0;
}

int confronta_interi(const int *n1,const int *n2){

	if(*n1<*n2)
		return -1;
	else if(*n1>*n2)
		return 1;
	else 
		return 0;
}

void stampa_array(int *a,int dim){
	
	for(int i=0;i<dim;i++)
		fprintf(stdout,"%d\t",a[i]);
	fprintf(stdout,"\n");
}

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_FAILURE);
}


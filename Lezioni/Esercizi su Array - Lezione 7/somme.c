/*
2) Scrivere una funzione C

int *somme_parziali(int a[], int n)
che dato un array di interi a[] di lunghezza n>0 alloca e restituisce un nuovo array b[] sempre di lunghezza n tale che b[i] = a[0] + a[1] + ... + a[i]. 
Si scriva poi un programma somme che invoca somme_parziali passandogli l'array ottenuto convertendo in interi i valori forniti sulla linea di comando e successivamente stampa l'array restituito da somme_parziali. Ad esempio:

somme 1 2
1 3
somme 2 3 1 10 -1
2 5 6 16 15

*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

int *somme_parziali(int a[], int n);
void termina(const char messaggio[]);

int main(int argc,char *argv[]){
	
	//bisogna passare al programma dei numeri che saranno gli elementi che appartengono al vettore
	if(argc==1)
		termina("Uso: x1 x2 x3 ... xn");
		
	int dim = argc-1;
	assert(dim>1);
	
	int *a = malloc(dim*sizeof(int));
	
	if(a==NULL)
		termina("Errore malloc");
		
	for(int i = 0;i<dim;i++)
		a[i] = atoi(argv[i+1]);
	
	for(int i = 0;i<dim;i++)
		fprintf(stdout,"%d \t",a[i]);
	fprintf(stdout,"\n");
	
	int *b = somme_parziali(a,dim);
	
	for(int i = 0;i<dim;i++)
		fprintf(stdout,"%d \t",b[i]);
	fprintf(stdout,"\n");
	
	return 0;
}

int *somme_parziali(int a[], int n){
	
	int *b = malloc(sizeof(int)*n);
	
	if(b==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<n;i++)
		for(int j = 0;j<=i;j++)
			b[i] += a[j];
			
	return b;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

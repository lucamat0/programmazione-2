/* *********************************************************
 * primiab.c
 * 
 * Legge due interi a e b dalla linea di comando 
 * e crea una tabella con i primi comnpresi tra a e b
 * 
 * Compilate scrivendo:
 *   gcc -g -Wall -O -std=c99 -o primiab primiab.c
 * ********************************************************* */
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

bool primo(int n);
void termina(const char messaggio []);

int main(int argc,char *argv[]){
	
	if(argc != 3)
		termina("Uso: intero_a intero_b");
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	if(a>b)
		termina("L'intero_b deve essere piu' grande del intero_a");
	else if(a<=1 && b<=1)
		return 0;
	else if(a==b){
		if(primo(a))
			fprintf(stdout,"%d\n",a);
		return 0;
	}
	
	assert(b>a);
	assert(b>0);
		
	int dim = b;
	int *myVector = malloc(dim*sizeof(int));
	
	if(myVector==NULL)
		termina("Errore malloc");
	
	int messi = 0;
	for(int i = a;i<=b;i++){
		if(primo(i)){
			myVector[messi] = i;
			messi++;
		}
	}
	
	dim = messi;
	myVector = realloc(myVector,dim*sizeof(int));
	
	if(myVector==NULL)
		termina("Errore realloc");
	
	for(int i = 0;i<dim;i++){
		fprintf(stdout,"%d\t",myVector[i]);
	}
	fprintf(stdout,"\n");
	
	free(myVector);
	return 0;
}

bool primo(int n){
	
	//un numero per essere definito primo deve essere maggiore di 1.
	if(n<=1)
		return false;
		
	for(int i = 2;i<n;i++){
		if(n%i==0)
			return false;
	}
	return true;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

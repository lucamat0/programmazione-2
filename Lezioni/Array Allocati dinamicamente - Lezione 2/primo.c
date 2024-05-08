#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

//i numeri primi sono tutti maggiori di 1, devono essere divisibili solamente da 1.
bool primo(int n);

int main(int argc, char *argv[]){
	
	if(argc != 2)
		termina("Uso: intero_da_testare");
	
	int n = atoi(argv[1]);
	
	//i numeri primi sono tutti maggiori di 1
	if(n<=1)
		termina("L'intero deve essere maggiore di 1");
	
	//soluzione con un array allocati nello stack
	//->lo stack non puo' contenere n molto grandi 
	//->abbiamo allocato della memoria che non abbiamo utilizzato.
	int a[n];
	
	int messi = 0;
	for(int i = 0;i<n;i++){
		if(primo(i)){
			a[messi] = i;
			messi += 1;
		}
	}
	
	//stampo gli elementi che contiene il vettore
	
	for(int i = 0;i<messi;i++)
		fprintf(stdout,"%d \t",a[i]);
	fprintf(stdout,"\n");
	
	//malloc(quanti_elementi_voglio*sizeof(tipo_variabile));
	//l'array dinamico si trova nel heap
	int *b = malloc(n*sizeof(int));
	
	if(b==NULL){termina("Errore malloc");}
	
	int messib = 0;
	for(int i = 0;i<n;i++){
		if(primo(i)){
			b[messib] = i;
			messib += 1;
		}
	}
	
	//array dinamici =  la dimensione puo' variare durante l'esecuzione del programma
	b = realloc(b,messib*sizeof(int));
	
	if(b==NULL){termina("Errore realloc");}
	
	for(int i = 0;i<messib;i++)
		fprintf(stdout,"%d \t",b[i]);
	fprintf(stdout,"\n");
	
	//dealloco l'array che non utilizzo piu'
	free(b);
		
	return 0;
}

bool primo(int n){
	
	//n>1 quindi potrebbe essere un numero primo.
	for(int i = 2;i<n;i++){
		//se il resto della divisione di n e i vale 0 allora il numero non sara' primo
		//ho scoperto un divisore.
		if(n%i == 0)
			return false;
	}
	return true;
 }
 
 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


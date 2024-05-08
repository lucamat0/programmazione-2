/*
Scrivere un programma nfib che prende in input sulla linea di comando un intero n crea un array di interi contenenti i primi n numeri Fibonacci. Si ricorda che i numeri di Fibonacci sono dati dalla formula

F_0 = 1,  
F_1 = 1, 
F_2 = F_0 + F_1 = 2
F_3 = F_1 + F_2 = 3
F_4 = F_3 + F_2 = 5
e in generale ogni nuovo numero della sequenza è ottenuto dalla somma dei due numeri precedenti.

Dopo che l'array è stato riempito i suoi valori devono essere stampati sul terminale con l'istruzione printf. Quindi scrivendo sulla linea di comando

nfib 11
devono essere stampati sul terminale gli interi

1 1 2 3 5 8 13 21 34 55 89
*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: numero_di_interi_da_stampare");
	
	if(atoi(argv[1])<=0)
		termina("Per calcolare il numero di fibonacci devi inserire un intero positivo");
	else if(atoi(argv[1])==1)
		fprintf(stdout,"1\n");
	else{
	
		int dim = atoi(argv[1]);
		int *a = malloc(dim*sizeof(int));
		
		if(a==NULL)
			termina("Errore malloc");
		
		a[0] = 1;
		a[1] = 1;
		
		int messi = 2;
		for(int i = 2;i<atoi(argv[1]);i++){
			a[i] = a[i-1] + a[i-2];
			messi++;
		}
		
		dim = messi;
		a = realloc(a,dim*sizeof(int));
		
		if(a == NULL)
			termina("Errore realloc");
		
		for(int i = 0;i<dim;i++)
			fprintf(stdout,"%d \t",a[i]);
		fprintf(stdout,"\n");
		
		free(a);
	}
	
}

 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

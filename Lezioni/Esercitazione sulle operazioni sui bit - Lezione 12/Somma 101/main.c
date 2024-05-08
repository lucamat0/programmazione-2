/*
Scrivere un programma che legge un intero positivo n sulla 
linea di comando e restituisce la somma di tutti gli interi 
positivi minori di n la cui rappresentazione binaria termina
con 101.

Ad esempio, se viene passato il valore 12 il programma deve 
stampare su stdout il valore 5, in quanto tra gli interi 
tra 1 e 11, l'unico la cui rappresentazione binaria termini 
per 101 è il 5.
* 
Dopo che avete scritto e testato il vostro programma, 
dando il comando verifica.py sulla linea di comando verrà 
controllata la correttezza del vostro programma su alcuni 
esempi di test. 
Questa verifica richiede che l'eseguibile si chiami main 
e che su stdout venga scritto solamente il risultato finale.
*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: intero_x");
	
	int n = atoi(argv[1]);

/*
		1<<0 -> 001
		1<<1 -> 010
		1<<2 -> 100
		or    111

		101 = 5
  */
	int somma = 0;			
	for(int i=1;i<n;i++){
		if((i & (1<<0 | 1<<1 | 1<<2)) == 5)
			somma += i;
	}
	
	return 0;
}

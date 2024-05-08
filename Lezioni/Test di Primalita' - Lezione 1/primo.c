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
		termina("Uso: intero_da_testare\n");
	
	int n = atoi(argv[1]);
	
	if(primo(n) == true)
		fprintf(stdout,"Il seguente numero e' primo!\n");
	else
		fprintf(stdout,"Il seguente numero e' composto!\n");
		
	return 0;
}

bool primo(int n){
	
	//i numeri primi sono tutti maggiori di 1
	if(n<=1)
		return false;
	
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

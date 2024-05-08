#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

int somma(int a,int b);
int prodotto(int a,int b);

int applica(int a,int b,int (*f)(int,int));

int main(int argc,char *argv[]){

	if(argc != 3)
		termina("Uso: intero_a intero_b");
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	int r = applica(a,b,&somma);
	fprintf(stdout,"r: %d\n",r);
	
	r = applica(a,b,&prodotto);
	fprintf(stdout,"r: %d\n",r);
	
	return 0;
}

int applica(int a,int b,int (*f)(int,int)){

	return f(a,b);
}

int somma(int a,int b){
	return a+b;
}

int prodotto(int a,int b){
	return a*b;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

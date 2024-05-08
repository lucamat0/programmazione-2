#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

int main(int argc,char *argv[]){
	
	if(argc!=4)
		termina("Uso: intero_a intero_b operazione_da_eseguire");
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	int c;
	if(strcmp(argv[3],"and")==0)
		c = a & b;
	else if(strcmp(argv[3],"or")==0)
		c = a | b;
	else if(strcmp(argv[3],"shift")==0)
		c = a << b;
	else 
		termina("Il terzo parametro deve contenere: and/or/shift");
	
	fprintf(stdout,"Risultato: %d\n",c);	
	
	return 0;
}	

 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

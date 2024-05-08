#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

int main(int argc,char *argv[]){
	
	if(argc !=2)
		termina("Uso: intero");
	
	int a = atoi(argv[1]);
	
	//32 bit (4 byte per esprimere un intero) + 1 carattere di fine stringa
	char risultato[33];
	
	for(int i = 0;i<32;i++){
		if((a & (1<<i)) != 0 )
			risultato[i] = '1';
		else
			risultato[i] = '0';
	}
	
	//completo il risultato con il fine stringa 
	risultato[32] = '\0';
	
	for(int i = 32;i>=0;i--)
		fprintf(stdout,"%c",risultato[i]);
	fprintf(stdout,"\n");	
	//fprintf(stdout,"%s\n",risultato);
	
	return 0;
}


 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

int bin2dec(char numerobinario[]);

void termina(const char messaggio []);

int main(int argc,char *argv[]){
	
	if(argc != 2)
		termina("Uso: numero_binario_da_convertire");
	
	int risultato = bin2dec(argv[1]);
	
	fprintf(stdout,"Risultato: %d\n",risultato);
	fprintf(stdout,"Risultato con strtol: %ld\n",strtol(argv[1],NULL,2));
	return 0;
}

//prende in input un numero binario e restituisce un intero in rappresentazione deciamale
int bin2dec(char numerobinario[]){
	
	int num = 0;
	for(int i = 0;i<strlen(numerobinario);i++)
		if(numerobinario[i] == '1'){
			int pos = strlen(numerobinario)-1-i;
			num = num | 1<<pos;
		}
		else if(numerobinario[i] != '0')
			termina("Non e' stato passato un numero binario!");
			
	return num;
}

 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

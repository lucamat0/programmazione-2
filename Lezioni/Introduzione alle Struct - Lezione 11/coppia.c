#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct coppiaint{
	int x;
	int y;
}coppia;

void termina(const char messaggio []);

coppia raddoppia(coppia c);

void stampa_coppia(coppia c);
	
int main(int argc,char *argv[]){
	
	if(argc != 3)
		termina("Uso: intero_x intero_y");
	
	coppia c;
	c.x = atoi(argv[1]);
	c.y = atoi(argv[2]);
	
	coppia a = raddoppia(c);
	
	stampa_coppia(c);
	stampa_coppia(a);
	
	return 0;
}
//restituisce una coppia di elementi con il doppio del valore della coppia c
coppia raddoppia(coppia c){
	coppia cp;
	
	cp.x = 2 * c.x;
	cp.y = 2 * c.y;
	
	return cp;
}

void stampa_coppia(coppia c){
	fprintf(stdout,"x: %d y: %d\n",c.x,c.y);
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

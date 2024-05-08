// main.c per testare esercizio sulle liste di coppie 
// da compilare separatamente da coppie.c
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

#include "coppie.h"

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

bool positivi(int a, int b){
  return a>0 && b>0;
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Uso: %s nomefile\n",argv[0]);
        return 1;
    }
    
    coppia *lista = crea_lista(argv[1]);
    puts("--- Stampa Lista completa ---");
    stampa_lista_coppie(stdout,lista);
    puts("\n------");
    puts("--- Cerca coppia con somma + alta ---");
    coppia *maxc = cerca_coppia_maxsomma(lista);
    stampa_coppia(stdout,maxc);
    puts("\n------");
	puts("--- Cerca prima coppia positiva ---");
    coppia *lista2 = cerca_coppia(lista,positivi);
    stampa_coppia(stdout,lista2);
    puts("\n------");
	puts("--- Crea lista coppie positive ---");
    coppia *newLis = duplica_lista(lista,positivi);
    stampa_lista_coppie(stdout,newLis);
    puts("\n------");
    
    distruggi_lista_coppie(lista);
    return 0; 
}

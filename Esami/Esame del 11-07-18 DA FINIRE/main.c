#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

#include "coppie.h"

void termina(const char messaggio[]);

bool uguali(int a, int b){
  return a==b;
}
 
int main(int argc, char *argv[]){
	if(argc < 3) {
        printf("Uso: %s somma elemento [elemento]\n",argv[0]);
        return 1;
    }
    
    int somma = atoi(argv[1]);
    coppia *lista = NULL;
    
    for(int i=2;i<argc;i++) {
      int e = atoi(argv[i]);
      coppia *a = crea_coppia(e,2*e);
      lista = inserisci_coppia(lista,a);
    }
     
    stampa_lista_coppie(stdout,lista);
    cerca_e_stampa_coppie(stdout,lista, 45);
    printf("Coppie: %d\n",conta_coppie(lista,uguali));
    distruggi_lista_coppie(lista);
    return 0;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

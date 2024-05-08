#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

// stampa un messaggio di errore e termina
void termina(const char *messaggio);


int main(int argc, char *argv[])
{
  // alloca e inizializza array di 10 interi 
  int *a = malloc(10*sizeof(int));
  for(int i=0;i<10;i++)
    a[i] = i;  
  
  // a contiene l'indirizzo del primo elemento dell'array 
  printf("Indirizzo memorizzato in a: %p\n",a);
  printf("Indirizzo di a[0]: %p\n",&a[0]);
  
  // esempio di aritmetica dei puntatori
  for(int i=0;i<10;i++) {
    int *b = a + i; // somma tra puntatore e intero;  a+i è una scorciatoia per &a[i]
    printf("%d) indirizzo in b: %p, indirizzo di a[%d]: %p\n",i,b,i,&a[i]);
    printf("Valore a cui punta b: %d\n", *b);
  }
  
  // aritmetica dei puntatori per un array di char
  char *s = "ciao";
  for(int i=0;i<5;i++) {
    char *b = s+i; // somma tra un puntatore e un intero 
    printf("%d) indirizzo in b: %p, carattere a cui punta b: %c\n",i,b,*b);
  }
  
  // esempio di accesso a una posizione esterna all'array
  char * b = s+100;       // semplicemente calcolare la posizione non dà errore anche se siamo fuori dall'array
  printf("Posizione fuori dal mio array: %p\n", b); 
  *b = ' ';               // scrivere in una posizione fuori dell'array puo' causare un segfault 
  
  return 0;
}


// mostra il messaggio d'errore passato come parametro seguito
// dal messaggio associato all'ultimo errore di una funzione di libreria
// (mediante errno); dopo la stampa termina il programma  
void termina(const char *messaggio)
{
  perror(messaggio);
  exit(EXIT_FAILURE);
}

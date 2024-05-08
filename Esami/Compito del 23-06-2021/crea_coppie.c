#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit()
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

//#include "coppie.h"

int main(int argc, char *argv[])
{
    if(argc < 4 || argc%2!=0) {
        printf("Uso: %s nomefile i1 i2 i3 i4 i5 i6 ....\n",argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1],"wb");
    for(int i=2;i<argc;i++) {  
      int n = atoi(argv[i]);
      if(fwrite(&n,sizeof(int),1,f)!=1) {
         perror("Errore scrittura"); exit(1);
      }
    }
    fclose(f);
    return 0;
}

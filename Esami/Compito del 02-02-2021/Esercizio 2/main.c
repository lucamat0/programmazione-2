//Esercizio 2
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(char messaggio[]);

/*
2a) Scrivere una funzione

int map(int a[], int n, int fun(int, int))
che dato un array a[] di n>1 interi, e una funzione fun calcola le quantità b(0), b(1), b(2), ... b(n-2)

    b(0) = fun(a[0],a[1])
    b(1) = fun(b(0),a[2])
    b(2) = fun(b(1),a[3])
    ... 
fino a

    b(n-2) = fun(b(n-3),a[n-1])
e restituisce il valore b(n-2)

Ad esempio se a = {2,4,0,1} e la funzione somma e' definita da

  int somma(int a, int b) {
    return a+b;
  }
allora l'invocazione map(a,4,somma) deve restituire 7 (uguale a 2+4+0+1)


*/
int map(int a[], int n, int fun(int, int));

int sottrazione(int a,int b);

int op(int a,int b){
	return 1+(a*b);
}

int main(int argc,char *argv[]){
	
	if(argc<=1)
		termina("Errore, passa gli elementi per riempire l'array!");
		
	int a[argc-1];
	for(int i = 0;i<argc-1;i++){
		a[i] = atoi(argv[i+1]);
	}
	
	for(int i = 0;i<argc-1;i++){
		fprintf(stdout,"%d \t",a[i]);
	}
	fprintf(stdout,"\n");
	
	int dim = argc-1;
	int ris = map(a,dim,sottrazione);
	fprintf(stdout,"\nLa sottrazione e': %d\n",ris);
	
	ris = map(a,dim,op);
	fprintf(stdout,"\nOp e': %d\n",ris);
	return 0;
}

int map(int a[],int dim,int (fun)(int,int)){
	
	int b = fun(a[0],a[1]); 	
	
	fprintf(stdout,"%d\t",b);
	
	for(int i = 2;i<dim-2;i++){		 	
		b = fun(b,a[i]); 			
		fprintf(stdout,"%d\t",b);
	}
	
	return b;
}

int sottrazione(int a,int b){
	return a-b;
}

void termina(char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_FAILURE);
}

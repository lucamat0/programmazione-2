/*
3) Scrivere un programma in C che legge una sequenza di interi sulla linea di comando e stampa il più grande valore che appaia almeno 2 volte. 
Il programma deve stampare un messaggio di errore se nessun valore appare almeno due volte. 

Esempi:
max2v 3 -5 7 2 7 2 2 -5 100 2 1000 -5
-> 7   [solo  7, 2 e -5 appaiono piu' di una volta]
max2v 3 -5 7 -2 17 -5 100 -2 1000 -5
-> -2   [solo -2 e -5 appaiono piu' di una volta]
max2v 100 1000 1 2 3 -4
-> Errore, nessun valore appare almeno 2 volte
Suggerimento: per prima cosa si costruisca l'array contenente tutti gli interi passati sulla linea di comando. Successivamente scrivere una funzione

int *doppi(int a[], int n, int *m)
che dato un array di interi a[] restituisce un nuovo array di interi b[] contenente gli elementi di a[] che appaiono almeno due volte, e calcolare poi il massimo degli elementi di b[] utilizzando la funzione max_array dell'esercizio 1.
*/
#include <stdio.h>    // permette di usare scanf printf etc
#include <stdlib.h>   // conversioni stringa/numero exit() etc 
#include <stdbool.h>  // gestisce tipo bool 
#include <assert.h>   // permette di usare la funzione assert

int *doppi(int a[], int n, int *m);
int max_array(int a[], int n);

void termina(const char messaggio[]);

int main(int argc, char *argv[]){
	
	//bisogna passare al programma dei numeri che saranno gli elementi che appartengono al vettore
	if(argc==1)
		termina("Uso: x1 x2 x3 ... xn");
	
	int dima = argc-1;
	int *a = malloc(dima*sizeof(int));
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<dima;i++)
		a[i] = atoi(argv[i+1]);
	
	int dimb = 0;
	int *b = doppi(a,dima,&dimb);
	
	for(int i = 0;i<dimb;i++)
		fprintf(stdout,"%d \t",b[i]);
	fprintf(stdout,"\n");
	
	int max_b = max_array(b,dimb);
	fprintf(stdout,"Elemento massimo: %d\n",max_b);

		
	return 0;
}

int *doppi(int a[], int n, int *m){

	int messi = 0;
	int *b = malloc(sizeof(int)*n);
	
	if(b==NULL)
		termina("Errore malloc");
	
	int conta = 1;
	for(int i = 0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(a[i]==a[j])
				conta++;
		}
		if(conta>1){
			
			bool find = false;
			for(int j = 0 ;j<messi;j++)
				if(a[i] == b[j])
					find = true;
			
			if(!find){
				b[messi] = a[i];
				messi++;
			}
			conta = 1;	
		}
	}
	
	if(messi==0)
		termina("Errore, nessun valore appare almeno due volte.");
	
	b = realloc(b,sizeof(int)*messi);
	
	if(b==NULL)
		termina("Errore realloc");
	
	*m = messi;
	
	return b;
}


void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

int max_array(int a[], int n){
	
	assert(n>0);
	
	int max_num = a[0];
	for(int i = 0;i<n;i++){
		if(a[i]>max_num)
			max_num = a[i];
	}

	return max_num;
}

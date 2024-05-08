/*
1) Scrivere una funzione C

int max_array(int a[], int n)
che dato un array di interi a[] di lunghezza n>0 restituisce il valore del massimo elemento di a[]. Si scriva poi un programma in C maxa che invoca la funzione max_array passandogli l'array ottenuto convertendo in interi i valori forniti sulla linea di comando e stampa il valore restituito da max_array. Ad esempio:

maxa 12 -5 3 20 4
Massimo: 20
Utilizzare la funzione atoi per convertire in interi le stringhe contenute in argv secondo lo schema visto a lezione.

*/

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

int max_array(int a[], int n);

void termina(const char messaggio []);

int main(int argc,char *argv[]){

	//bisogna passare al programma dei numeri che saranno gli elementi che appartengono al vettore
	if(argc==1)
		termina("Uso: x1 x2 x3 ... xn");
	
	int dim = argc-1;
	int *a = malloc(sizeof(int)*dim);
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<dim;i++)
		a[i] = atoi(argv[i+1]);
	
	for(int i = 0;i<dim;i++)
		fprintf(stdout,"%d\t",a[i]);
	fprintf(stdout,"\n");
	
	int max_num = max_array(a,dim);
	
	fprintf(stdout,"Elemento massimo: %d\n",max_num);
	
	free(a);
	
	return 0;

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

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


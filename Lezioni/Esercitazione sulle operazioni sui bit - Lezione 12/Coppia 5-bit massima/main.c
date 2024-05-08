/*
Scrivere una funzione

int max5somma(int a[], int n)

che dato un array a di n interi modifica tutti gli elementi 
di a ponendo a zero tutto i bit tranne i 5 meno significativi.

Successivamente la funzione deve calcolare e restituire il 
massimo valore ottenibile come somma di due elementi 
distinti dell'array a così modificato.

Scrivere poi un main che legge il nome di un file di testo 
dalla linea di comando. 
Tale file contiene sulla prima riga un numero positivo n e 
sulla seconda riga n interi positivi. 
Il programma deve copiare questi interi in un array di n 
elementi, passare questo array alla funzione max5somma e 
visualizzare su stdout il valore restituito dalla funzione.

Ad esempio, se viene passato il nome del file test1 che al 
suo interno contiene

4
128 15 40 77

deve essere creato (dinamicamente!) un array con i 4 
elementi della seconda riga, tale array deve poi essere 
passato alla funzione max5somma che prima modifica gli 
elementi ponendo a zero tutti i bit tranne i 5 meno 
significativi (gli elementi di a diventano quindi 0, 15, 8 
e 13) e successivamente restituisce il valore 28 
(corrispondente alla massima somma tra due elementi di a). 
Infine il main deve stampare tale valore su stdout, 
deallocare tutta la memoria utilizzata e terminare.

Dopo che avete scritto e testato il vostro programma, 
il comando verifica.py dato nella console controllerà la 
correttezza del vostro programma sui file di test. 
Questa verifica richiede che l'eseguibile si chiami main e 
che su stdout venga scritto solamente il risultato finale.
*/

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

int max5somma(int a[], int n);

void stampa_array(int a[],int dim,FILE *pFile);

int main(int argc,char *argv[]){

	if(argc!=2)
		termina("Uso: nome_del_file");
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	int dim;
	if(fscanf(pFile,"%d",&dim)!=1)
		termina("Errore fscanf 1");
	
	int *a = malloc(sizeof(int)*dim);
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i=0;i<dim;i++)
		if(fscanf(pFile,"%d ",&a[i]) != 1)
			termina("Errore fscanf 2");
	
	
	stampa_array(a,dim,stdout);
	
	int somma_max = max5somma(a,dim);

	stampa_array(a,dim,stdout);
	fprintf(stdout,"Somma max: %d\n",somma_max);
	
	fclose(pFile);
	free(a);
}

void stampa_array(int a[],int dim,FILE *pFile){

	for(int i=0;i<dim;i++)
		fprintf(pFile,"%d\t",a[i]);
	fprintf(pFile,"\n");
}

int max5somma(int a[], int n){
	
	assert(n>1);
	
	int el;
	for(int i=0;i<n;i++){
		el = (a[i] & (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 ));
		a[i] = el;
	}
	
	int somma_max = a[0];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i!=j)
				if(a[i]+a[j]>somma_max)
					somma_max = a[i]+a[j];
		}
	}
		
	return somma_max;
}

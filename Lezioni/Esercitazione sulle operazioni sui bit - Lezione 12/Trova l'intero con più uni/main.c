/*
Scrivere una funzione

int piuuni(int a[], int n)

che dato un array a di n interi calcola e restituisce 
l'elemento la cui rappresentazione binaria contiene il 
maggior numero di 1. Se ci sono due elementi con lo stesso 
numero di uni, il programma deve restituire il più grande.

Scrivere poi un main che legge il nome di un file di testo 
dalla linea di comando. 
Tale file contiene sulla prima riga un numero positivo n e 
sulla seconda riga n interi positivi. 
Il programma deve copiare questi interi in un array di n 
elementi, passare questo array alla funzione piuuni e 
visualizzare su stdout il valore restituito dalla funzione.

Ad esempio, se viene passato il nome del file test1 che 
al suo interno contiene:

4
8 2 3 0

deve essere creato (dinamicamente!) un array con i 4 
elementi della seconda riga, tale array deve poi essere 
passato alla funzione piuuni che dovrebbe restituire il 
valore 3. 
Infine il main deve stampare tale valore su stdout, 
deallocare tutta la memoria utilizzata e terminare.

Dopo che avete scritto e testato il vostro programma, il comando verifica.py dato nella console controllerà la correttezza del vostro programma sui file di test. Questa verifica richiede che l'eseguibile si chiami main e che su stdout venga scritto solamente il risultato finale.
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

void stampa_array(int *a,int dim);

int piuuni(int a[], int n);

int main(int argc,char *argv[]){

	if(argc!=2)
		termina("Uso: nome_del_file");
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	int dim;
	if(fscanf(pFile,"%d",&dim) != 1)
		termina("Errore fscanf 1");
	
	int *a = malloc(sizeof(int)*dim);
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i=0;i<dim;i++)
		if(fscanf(pFile,"%d ",&a[i]) != 1)
			termina("Errore fscanf 2");
	
	stampa_array(a,dim);
	
	int n = piuuni(a,dim);
	fprintf(stdout,"Numero con piu' uni: %d\n",n);
	
	fclose(pFile);
	free(a);
	
	return 0;
}

int piuuni(int a[], int n){
	
	assert(n>0);
	
	int max_uni = 0;
	int num_max_uni = 0;
	
	int conta = 0;
	for(int i=0;i<n;i++){
		//for(int j=0;j<32;j++){	-> oppure questo.
		for(int j=0;j<=sizeof(int);j++){
			if((a[i] & (1<<j)) != 0)
				conta++;
		}
		if(conta>=max_uni){
			max_uni = conta;
			num_max_uni = a[i];
		}
		conta=0;
	}
	return num_max_uni;
}

void stampa_array(int *a,int dim){
	
	for(int i=0;i<dim;i++)
		fprintf(stdout,"%d\t",a[i]);
	fprintf(stdout,"\n");
}

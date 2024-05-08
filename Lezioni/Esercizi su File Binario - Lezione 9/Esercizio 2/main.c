/* *****************************************************
 * Calcola la somma degli interi tra 1 e 1000
 * che non appaiono in un file
 * ***************************************************** */
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

int *leggi_numeri_da_file(FILE *pFile,int *dim);
int somma_interi_non_contenuti_file(int *a,int dim);

void termina(const char messaggio[]);

int main(int argc,char *argv[]){
	
	if(argc != 2)
		termina("Uso: nome_del_file");
	
	FILE *pFile = fopen(argv[1],"rb");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	int dim = 0;
	int *a = leggi_numeri_da_file(pFile,&dim);
	fclose(pFile);
	
	assert(dim>0);
	
	int somma = somma_interi_non_contenuti_file(a,dim);
	
	fprintf(stdout,"somma: %d\n",somma);
	free(a);
	
	return 0;
}

int somma_interi_non_contenuti_file(int *a,int dim){

	int somma = 0;
	
	bool find = false;
	for(int i=1;i<=1000;i++){
		for(int j=0;j<dim;j++){
			if(a[j] == i)
				find = true;
		}
		if(find == false)
			somma += i;
		else 
			find = false;
	}
	
	return somma;
}

int *leggi_numeri_da_file(FILE *pFile,int *dim){
	
	assert(pFile != NULL);
	
	int e = fseek(pFile,0,SEEK_END);
	
	if(e<0)
		termina("Errore fseek");
	
	long lunghezza = ftell(pFile);
	
	assert(lunghezza>0);
	
	if(lunghezza<0)
		termina("Errore ftell");
		
	int interi = lunghezza/sizeof(int);
	
	assert(interi>0);
	
	int *a = malloc(sizeof(int)*interi);
	
	if(a==NULL)
		termina("Errore malloc");
	
	rewind(pFile);
	
	if(fread(a,sizeof(int),interi,pFile) != interi)
		termina("Errore fread");
	
	*dim = interi;
	return a;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


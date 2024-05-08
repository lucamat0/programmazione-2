/* *********************************************************
 * Calcola la somma degli interi che appaiono almeno  
 * 3 volte in un file 
 * ********************************************************* */
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

int *leggi_numeri_da_file(FILE *pFile,int *dim);
int calcola_somma_interi_appaiono_almeno_tre_volte(int *a,int dim);

void termina(char messaggio[]);

int main(int argv, char *argc[]){
	
	if(argv != 2)
		termina("Uso: nome_file");
		
	FILE *pFile = fopen(argc[1],"rb");
	
	if(pFile==NULL)
		termina("Errore fopen");
	
	int dim;
	int *a = leggi_numeri_da_file(pFile,&dim);
	
	fclose(pFile);
	
	int somma = 0;
	somma = calcola_somma_interi_appaiono_almeno_tre_volte(a,dim);
	
	free(a);
	
	fprintf(stdout,"somma: %d\n",somma);

}

int *leggi_numeri_da_file(FILE *pFile,int *dim){

	assert(pFile != NULL);
	
	//sposto il puntatore al fondo del file
	if(fseek(pFile,0,SEEK_END)<0)		
		termina("Errore fseek");
		
	//otteniamo il numero di byte del file	
	long lunghezza = ftell(pFile);
	
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

int calcola_somma_interi_appaiono_almeno_tre_volte(int *a,int dim){
	
	int somma = 0;
	int conta = 0;
	
	int *b = malloc(sizeof(int)*dim);
	int messi = 0;
	
	if(b==NULL)
		termina("Errore malloc");
	
	int find = false;
	for(int i = 0;i<dim;i++){
		for(int x = 0;x<messi;x++){
			if(b[x]==a[i])
				find = true;
		}
		if(!find){
			b[messi] = a[i];
			messi++;
			
			for(int j = 0;j<dim;j++){
				if(a[i]==a[j])
					conta++;
			}
			if(conta>=3)
				somma+= a[i];
			conta = 0;
		}
		else
			find = false;
		
	}
	
	free(b);
	
	return somma;
}

void termina(char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE);
}

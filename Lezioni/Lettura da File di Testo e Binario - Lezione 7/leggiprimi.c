#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

//i numeri primi sono tutti maggiori di 1, devono essere divisibili solamente da 1.
bool primo(int n);

int *crea_array_numeri_primi(int n,int *dim);

int *leggi_array_file_testo(FILE *pFile,int *dim);
int *leggi_array_file_binario(FILE *pFile,int *dim);

int main(int argc, char *argv[]){
	
	if(argc != 3)
		termina("Uso: intero_da_testare numero_file_da_creare tipo_file_creare");
	
	bool formato = false;
	if(strcmp(argv[2],"b") == 0)
		formato = false;
	else if(strcmp(argv[2],"t") == 0)
		formato = true;
	else
		termina("Il secondo parametro deve essere b/t");
	
	FILE *pFile;
	if(formato)
		pFile = fopen(argv[1],"rt");
	else
		pFile = fopen(argv[1],"rb");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	//dimensione totale array
	int dim;
	//puntatore al primo elemento del array
	int *a;
	
	if(formato)
		a = leggi_array_file_testo(pFile,&dim);
	else 
		a = leggi_array_file_binario(pFile,&dim);
	
	assert(dim>0);
	
	for(int i = 0;i<dim;i++){
		fprintf(stdout,"%d\t",a[i]);
	}
	fprintf(stdout,"\n");
	
	
	//dealloco l'array che non utilizzo piu'
	free(a);
	
	if(fclose(pFile)==EOF)
		termina("Errore fclose");
	
	return 0;

}

int *leggi_array_file_testo(FILE *pFile,int *dim){
	
	int dimA = 1;
	int messi = 0;
	int *a = malloc(sizeof(int)*dimA);
	
	if(a==NULL)
		termina("Errore malloc");
	
	int tmp;
	while(fscanf(pFile,"%d",&tmp) != EOF){
		if(messi==dimA){
		
		dimA *= 2;
		a = realloc(a,dimA*sizeof(int));
		a[messi] = tmp;
		messi++;	
		
		}
		else{
			
			assert(dimA>messi);
			
			a[messi] = tmp;
			messi++;
		}
	}
	
	a = realloc(a,sizeof(int)*messi);
	
	if(a==NULL)
		termina("Errore realloc");

	*dim = messi;
	return a;
}

int *leggi_array_file_binario(FILE *pFile,int *dim){
	
	//1)capire quanti sono gli interi che sono memorizzati sul file
	//2)allocare l'array
	//3)copiare gli interi dal file al array
	//4)restituire l'array
	
	assert(pFile!=NULL);
	
	//sposto al fondo il puntatore all'interno del file
	int e = fseek(pFile,0,SEEK_END);
	
	if(e<0)
		termina("Errore fseek");
	
	assert(e>=0);
	
	//otteniamo il numero di byte del file	
	long lunghezza = ftell(pFile);
	
	assert(lunghezza>0);
	
	if(lunghezza<0)
		termina("Errore fteel");
	
	int interi = lunghezza/(sizeof(int));
	
	assert(interi>0);
	
	//alloco l'array di dimensione opportune
	int *a = malloc(interi*sizeof(int));
	
	if(a==NULL)
		termina("Malloc fallita");
	
	//porta il puntatore all'inizio del file
	rewind(pFile);
	
	//leggo e copio gli elementi che si trovano all'interno del file all'interno dell'array a
	if(fread(a,sizeof(int),interi,pFile) != interi)
		termina("Errore fread");
	
	*dim = interi;
	return a;
}
 
 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


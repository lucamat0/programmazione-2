#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

//i numeri primi sono tutti maggiori di 1, devono essere divisibili solamente da 1.
bool primo(int n);

int *crea_array_numeri_primi(int n,int *dim);

void scrivi_array_file_binario(FILE *pFile,int *a,int dim);

int main(int argc, char *argv[]){
	
	if(argc != 3)
		termina("Uso: intero_da_testare numero_file_da_creare");
	
	int n = atoi(argv[1]);
	
	//i numeri primi sono tutti maggiori di 1
	if(n<=1)
		termina("L'intero deve essere maggiore di 1");
	
	//tenta di aprire il file, la b e' solo un nostro promemoria, il compilatore non la guarda
	FILE *pFile = fopen(argv[2],"wb");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	int dim;
	int *a = crea_array_numeri_primi(n,&dim);
	
	scrivi_array_file_binario(pFile,a,dim);

	//dealloco l'array che non utilizzo piu'
	free(a);
	
	if(fclose(pFile)==EOF)
		termina("Errore fclose");
	
	return 0;
}

void scrivi_array_file_binario(FILE *pFile,int *a,int dim){
	
	
	//scrive tutti i numeri in un colpo solo
	//restitiusce il numero di oggetti scritti sul file
	if(fwrite(a,sizeof(int),dim,pFile) != dim)
		termina("Errore fwrite");
	
	/*
	
	OPPURE: 
	for(int i = 0;i<dim;i++){
		if(fwrite(&a[i],sizeof(int),1,pFile) != 1)
			termina("Errore fwrite");
	}
	
	*/
	
	
}

int *crea_array_numeri_primi(int n,int *dim){
	
	//malloc(quanti_elementi_voglio*sizeof(tipo_variabile));
	//l'array dinamico si trova nel heap
	int *a = malloc(n*sizeof(int));
	
	if(a==NULL){termina("Errore malloc");}
	
	int messi = 0;
	for(int i = 2;i<n;i++){
		if(primo(i)){
			a[messi] = i;
			messi += 1;
		}
	}
	
	//array dinamici =  la dimensione puo' variare durante l'esecuzione del programma
	a = realloc(a,messi*sizeof(int));
	
	if(a==NULL){termina("Errore realloc");}
	
	*dim = messi;
	return a;
}

bool primo(int n){
	
	//n>1 quindi potrebbe essere un numero primo.
	for(int i = 2;i<n;i++){
		//se il resto della divisione di n e i vale 0 allora il numero non sara' primo
		//ho scoperto un divisore.
		if(n%i == 0)
			return false;
	}
	return true;
 }
 
 void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


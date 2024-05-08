#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio []);

//i numeri primi sono tutti maggiori di 1, devono essere divisibili solamente da 1.
bool primo(int n);

int *crea_array_numeri_primi(int n,int *dim);

void scrivi_array_file_testo(FILE *pFile,int *a,int dim);
void scrivi_array_file_binario(FILE *pFile,int *a,int dim);

int main(int argc, char *argv[]){
	
	if(argc != 4)
		termina("Uso: intero_da_testare numero_file_da_creare tipo_file_creare");
	
	int n = atoi(argv[1]);
	
	//i numeri primi sono tutti maggiori di 1
	if(n<=1)
		termina("L'intero deve essere maggiore di 1");
	
	bool formato = false;
	if(strcmp(argv[3],"b") == 0)
		//per completezza andiamo a rispecificare il valore della variabile formato.
		formato = false;
	else if(strcmp(argv[3],"t") == 0)
		formato = true;
	else
		termina("Il terzo parametro deve essere b/t");
	
	int dim;
	int *a = crea_array_numeri_primi(n,&dim);
	
	FILE *pFile;
	switch(formato){
		case true:
			//tenta di aprire il file
			pFile = fopen(argv[2],"wt");
			
			if(pFile == NULL)
				termina("Errore fopen");
			
			scrivi_array_file_testo(pFile,a,dim);
		break;
		case false:
			//tenta di aprire il file
			pFile = fopen(argv[2],"wb");
			
			if(pFile == NULL)
				termina("Errore fopen");
		
			scrivi_array_file_binario(pFile,a,dim);
		break;
	}
	
	//dealloco l'array che non utilizzo piu'
	free(a);
	
	if(fclose(pFile)==EOF)
		termina("Errore fclose");
	
	return 0;
}

void scrivi_array_file_testo(FILE *pFile,int *a,int dim){
	
	//per vedere il valore di ritorno di ogni funzione basta utilizzare il terminale, scrivendo:
	//man 3 nome_funzione
	for(int i = 0;i<dim;i++)
		if(fprintf(pFile,"%d \t",a[i])<0)
			termina("Errore fprintf1");
	if(fprintf(pFile,"\n")<0)
		termina("Errore fprintf2");
}

void scrivi_array_file_binario(FILE *pFile,int *a,int dim){
	
	//scrive tutti i numeri in un colpo solo
	//restitiusce il numero di oggetti scritti sul file
	if(fwrite(a,sizeof(int),dim,pFile) != dim)
		termina("Errore fwrite");
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


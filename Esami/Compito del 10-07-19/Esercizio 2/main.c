#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]);

/*
2a) Scrivere una procedura

void triangolo(FILE *f, int n)
che dato un intero positivo n scrive nel file f n+1 righe in formato testo. 
Per i=0,1,2,...,n l'iesima riga deve contenere tutte le stringhe composte da una lettera a e da i lettere b. Ad esempio invocando

triangolo(stdout, 5)

devono essere scritte su stdout le seguenti 6 righe di testo

a
ab ba
abb bab bba
abbb babb bbab bbba
abbbb babbb bbabb bbbab bbbba
abbbbb babbbb bbabbb bbbabb bbbbab bbbbba

*/

void triangolo(FILE *f, int n);

void termina(const char messaggio[]);

/*
2b) Scrivere una procedura

char **elenco(int n, int *num)

che dato un intero positivo n crea e restituisce un array contenente le stringhe viste sopra. 
La procedura deve restituire il puntatore al primo elemento dell'array e scrivere nella variabile 
num il numero di elementi nell'array (come abbiamo sempre fatto). Ad esempio, invocando

elenco(5,&num)
deve essere creato un array contenente le 21 stringhe mostrate sopra (in un ordine qualsiasi) e 
il valore 21 deve essere memorizzato nella variabile num.
*/

char **elenco(int n, int *num);

/*
2c) Scrivere un main che legge un intero positivo n dalla linea di comando, invoca triangolo(stdout, n) e successivamente 
elenco(n,&num) ottenendo un array di stringhe a che deve poi essere ordinato lessicograficamente con qsort e strcmp. 
Infine le stringhe così ordinate devono essere scritte su stderr. 
Se ad esempio n = 2, su stderr devono essere scritte le stringhe:

a
ab
abb
ba
bab
bba
*/
void stampa_array(char *s[],int dim);

int ordina_lessicograficamente(const char **s1,const char **s2);

int main(int argc,char *argv[]){
		
	if(argc!=3)
		termina("Uso: intero_n nome_del_file");
	
	FILE *pFile = fopen(argv[2],"wt");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	triangolo(pFile,atoi(argv[1]));
	
	int dim;
	char **myVectors = elenco(atoi(argv[1]),&dim);
	
	stampa_array(myVectors,dim);
	
	qsort(myVectors,dim,sizeof(char **),(__compar_fn_t)ordina_lessicograficamente);
	
	puts("---");
	stampa_array(myVectors,dim);
	
	for(int i=0;i<dim;i++){
		free(myVectors[i]);
	}
	free(myVectors);
	
	fclose(pFile);
	return 0;
}

void triangolo(FILE *f, int n){
	
	//n+1 righe/colonne
	assert(n>=1);
	
	for(int i = 0;i<n+1;i++){
		
			for(int j = 0;j<i;j++){
				
				for(int k=0;k<i;k++){
					if(k==j)
						fprintf(f,"a");
					else
						fprintf(f,"b");
				}
				fprintf(f," ");
			}
		fprintf(f,"\n");
	}
}

int ordina_lessicograficamente(const char **s1,const char **s2){
	return strcmp(*s1,*s2);
}

char **elenco(int n, int *num){
	
	assert(n>=1);
	
	int dim = n;
	int messi = 0;
	char **myVectors = malloc(sizeof(char **)*dim);
	
	if(myVectors==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<n+1;i++){
		for(int j = 0;j<i;j++){		
			char *s = malloc(sizeof(char *)*n);
			
			if(s==NULL){
				termina("Errore malloc 2");
			}
			
			for(int k=0;k<i;k++){
				if(k==j){
					s[k] = 'a';
					s[k+1] = '\0';
				}
				else{
					s[k] = 'b';
					s[k+1] = '\0';
				}
			}
			if(messi==dim){
				dim *= 2;
				myVectors = realloc(myVectors,sizeof(char **)*dim);
	
				if(myVectors==NULL)
					termina("Errore malloc");
			}
					
			myVectors[messi] = s;
			messi++;
		}
	}
	*num = messi;
	return myVectors;
}

void stampa_array(char *s[],int dim){
	
	for(int i=0;i<dim;i++)
		fprintf(stdout,"%s \n",s[i]);
	fprintf(stdout,"%d stringhe \n",dim);
}

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_FAILURE);
}

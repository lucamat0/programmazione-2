#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp
/*
2a) Si scriva una funzione

char **leggiparole(char *s, int *n)

che data una stringa s contenente un insieme di parole 
separate dal carattere : crea e restituisce un array di 
stringhe (quindi puntatori a char) contenente una copia 
delle parole di s nello stesso ordine in cui appaiono in s. 
La lunghezza dell'array creato deve essere memorizzata in *n.

Ad esempio, l'invocazione

leggiparole(strdup("uno:nessuno:centomila"),&n);
deve restituire il puntatore ad un array contenente le stringhe "uno", "nessuno", "centomila" in quest'ordine e memorizzare il valore 3 in n. Usare la funzione di libreria strtok per dividere la stringa s in singole parole.

*/

char **leggiparole(char *s, int *n);

/*
2b) Scrivere una funzione

int sommafun(char *a[], int n, int (*fun)(char *) )
che dato l'array a di n stringhe e una funzione fun che prende in input una 
stringa e restituisce un intero, applica fun a tutti gli elementi di lis e 
restituisce la somma dei valori così ottenuti
*/

int conta_caratteri(char a[]);

int sommafun(char *a[], int n, int (*fun)(char *) );

/*
2c) Scrivere una funzione

int contavocali(char *s)

che data una stringa s restituisce il numero di vocali in essa contenuta. 
Per vocali si intendono uno dei caratteri aeiouyAEIOUY.
*/
int contavocali(char *s);

/*
2d) Si scriva un main che passa una copia di argv[1] a leggiparole ottenendo un array 
di stringhe a. Successivamente deve invocare sommafun passandogli l'array a e la 
funzione contavocali come terzo argomento. Infine, la funzione main deve scrivere, 
in un file di testo di nome argv[2], il valore restituito da sommafun seguito dagli 
elementi dell'array a tutti su linee distinte. Ad esempio, l'invocazione

esercizio3 int:long:char:double prova.txt
deve creare un file prova.txt contenente le linee

6
int
long
char
double
Prima di terminare il programma deve deallocare tutta memoria utilizzata (usare valgrind per verificarlo).
*/

void termina(const char messaggio[]);

void stampa_stringhe(char a[],FILE *pFile);

int main(int argc,char *argv[]){

	if(argc != 3)
		termina("Uso: stringa_parole_separate_da_: file_destinazione");
	
	//numero di stringhe separate da ':' 
	int n = 0;
	char *s = strdup(argv[1]);
	
	char **a = leggiparole(s,&n);
	
	assert(n>0);
	
	for(int i = 0;i<n;i++){
		stampa_stringhe(a[i],stdout);
	}
	fprintf(stdout,"Valore n: %d\n",n);
	
	int ris = sommafun(a,n,&contavocali);
	fprintf(stdout,"Numero totale di vocali: %d\n",ris);
	
	FILE *pFile = fopen(argv[2],"wt");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	fprintf(pFile,"%d\n",ris);
	for(int i = 0;i<n;i++){
		stampa_stringhe(a[i],pFile);
	}
	
	free(s);
	free(a);
	fclose(pFile);
	
/*
	//numero di stringhe separate da ':' 
	int n = 0;
	char *s = strdup("uno:nessuno:centomila");
	
	char **a = leggiparole(s,&n);
	
	assert(n>0);
	
	for(int i = 0;i<n;i++){
		stampa_stringhe(a[i],stdout);
	}
	fprintf(stdout,"\nValore n: %d\n",n);
	
	//calcolo il numero totale di caratteri.
	int ris = sommafun(a,n,&conta_caratteri);
	fprintf(stdout,"Valore ris: %d\n",ris);
	
	for(int i = 0;i<n;i++){
		stampa_stringhe(a[i],stdout);
		
		int nvoc = contavocali(a[i]); 
		
		fprintf(stdout,": %d vocali\n",nvoc);
	}
*/
	
	return 0;
}

int contavocali(char *s){
	
	int n_vocali = 0;
	for(int i = 0;i<strlen(s);i++){
		
		char s1 = tolower(s[i]);
		
		if(s1 == 'a' || s1 == 'e' || s1 == 'i' || s1 == 'o' || s1 == 'u')
			n_vocali++;
	}
	return n_vocali;
}

int sommafun(char *a[], int n, int (*fun)(char *) ){
	int somma = 0;
	for(int i = 0;i<n;i++){
		somma += fun(a[i]);
	}
	return somma;
}

int conta_caratteri(char a[]){
	return strlen(a); 
}

void stampa_stringhe(char a[],FILE *pFile){
	fprintf(pFile,"%s\n",a);
}

char **leggiparole(char *s, int *n){
	
	assert(s != NULL);
	
	char *t = strtok(s,":");
	
	int dim = 2;
	int messi = 0;
	char **sVector = malloc(sizeof(char *)*dim);
	
	if(sVector == NULL)
		termina("Errore malloc");
	
	sVector[messi] = t;
	messi++;
	
	while((t = strtok(NULL,":")) != NULL){
		if(messi==dim){
			dim *= 2;
			sVector = realloc(sVector,sizeof(char *)*dim);
			
			if(sVector == NULL)
				termina("Errore realloc");
			
			sVector[messi] = t;
			messi++;
		}
		else{
			sVector[messi] = t;
			messi++;
		}
	}
	
	sVector = realloc(sVector,sizeof(char *)*messi);
			
	if(sVector == NULL)
		termina("Errore realloc");
		
	*n = messi;
	return sVector;
}

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}


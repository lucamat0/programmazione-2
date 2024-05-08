//legge un array di coppie dalla riga di comando 
//e voglio selezionare quale coppia ha
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct coppiaint{
	int x;
	int y;
}coppia;

void termina(const char messaggio []);

void stampa_coppia(coppia c);

coppia peso_max(coppia a[],int n);

int peso_coppia(coppia c);

int main(int argc,char *argv[]){
	
	//coppie.c + n coppie(2) 
	if(argc%2==0)
		termina("x1 y1 x2 y2 ... xn yn");
	
	int n = (argc-1)/2;
	//vado a definire un array di coppia
	coppia *a = malloc(n*sizeof(coppia));
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<n;i++){
		a[i].x = atoi(argv[2*i+1]);
		a[i].y = atoi(argv[2*i+2]);
	}
	
	for(int i = 0;i<n;i++)
		stampa_coppia(a[i]);
	
	coppia c = peso_max(a,n);
	
	fprintf(stdout,"Coppia di peso massimo: ");
	stampa_coppia(c);
	
	free(a);
}

//restituisce la coppia con peso massimo in un array non vuoto di coppie
coppia peso_max(coppia a[],int n){
	
	assert(n>0);
	
	coppia max_c = a[0];
	
	for(int i = 0;i<n;i++){
		if(peso_coppia(a[i]) > peso_coppia(max_c))
			max_c = a[i];
	}
	
	return max_c;
}

//calcola la somma degli elementi della coppia
int peso_coppia(coppia c){
	return c.x+c.y;
}

void stampa_coppia(coppia c){
	fprintf(stdout,"x: %d y: %d\n",c.x,c.y);
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


// operazioni su array di puntatori a citta

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(char messaggio[]);

//Utilizzare la struttura per rappresentare un elemento di una lista di interi
typedef struct el {
  int val;
  struct el *next;
} intero;

//Scrivere una funzione che dato un file di testo f contenente interi, restituisce una lista contenente tutti gli interi 
//del file mantenendo l'ordine in cui compaiono. Ad esempio, se il file contiene
intero *crea_lista(FILE *f);

intero *crea_intero(int num);

void stampa_lista(FILE *pFile,intero *lis);

intero *inserisci_coda(intero *lis,intero *i);

//1b) Scrivere una funzione
//che data una lista di interi lis restituisce la massima differenza fra due elementi 
//consecutivi della lista. Nell'esempio del punto precedente la massima differenza è 35 
//(differenza fra il secondo e il terzo elemento)
int maxdiff(intero *lis);

//1c) Scrivere una funzione
//che data una lista di interi lis cancella e dealloca tutti gli elementi 
//che contengono un intero multiplo di 5
intero *cancella5(intero *lis);

/*
1d) Scrivere una funzione main che:
-verifica che sia argc==2
-apre in lettura il file argv[1] e invoca la funzione crea_lista passondogli il file argv[1]
-visualizza su stderr gli elementi della lista (usando un while o una funzione apposita)
-invoca la funzione maxdiff e visualizza il risultato su stderr
-invoca la funzione cancella5 e visualizza su stderr la lista risultante
-chiude i file, dealloca tutta la memoria utilizzata (verificare con valgrind), e termina.
Si consiglia di testare il programma anche con il file contenente i seguenti interi

5 10 15 17 21 25 27 35 40 45 50 55 61 65 71
che dovrebbe visualizzare -2 come massima differenza e terminare visualizzando la lista 17 21 27 61 71.
*/

int main(int argv,char *argc[]){
	
	if(argv != 2)
		termina("Errore, bisogna passare il nome del file che contiene gli interi!");
	
	//FILE *pFile = fopen("interi.txt","rt");
	FILE *pFile = fopen(argc[1],"rt");
	
	if(pFile == NULL) 
		termina("Errore fopen");
	
	intero *lis = crea_lista(pFile);
	
	fclose(pFile);
	
	stampa_lista(stderr,lis);
	fprintf(stderr,"\n");	
	
	int max = maxdiff(lis);
	fprintf(stdout,"La massima differenza fra due elementi e': %d\n",max);
	
	lis = cancella5(lis);
	
	stampa_lista(stderr,lis);
	fprintf(stderr,"\n");
	
	return 0;
}

intero *crea_lista(FILE *f){

	int num;
	
	intero *lis = NULL;
	while(fscanf(f,"%d",&num) != EOF){
		
		//fprintf(stderr,"%d",num);
		intero *i = crea_intero(num);	
		
		lis = inserisci_coda(lis,i);
	}
	
	return lis;
}

int maxdiff(intero *lis){
	
	assert(lis != NULL);
	assert(lis->next != NULL);
	
	int mxdiff = lis->val - lis->next->val;
	
	intero *el = lis->next;
	while(el -> next != NULL){
		
		if(el->val - el->next->val > mxdiff)
			mxdiff = el->val - el->next->val;
		
		el = el->next;
	}
	
	return mxdiff;
}

intero *crea_intero(int num){
	
	intero *i = malloc(sizeof(intero));
	
	if(i==NULL)
		termina("Errore malloc");
		
	i->val = num;
	i->next = NULL;
	
	return i;
}

intero *inserisci_coda(intero *lis,intero *i){
	
	if(lis==NULL)
		return i;
	
	intero *tmp = inserisci_coda(lis->next,i);
	
	lis->next = tmp;
	
	return lis;
}

intero *cancella5(intero *lis){
	
	if(lis == NULL)
		return NULL;
	
	intero *tmp = cancella5(lis->next);
	
	if(lis->val %5 == 0){

		free(lis);
		
		return tmp;
	}
	
	lis->next = tmp;
	
	return lis;
}

void termina(char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_FAILURE);
}

void stampa_lista(FILE *pFile,intero *lis){
	
	if(lis==NULL)
		return;
	
	fprintf(pFile,"%d \t",lis->val);
	
	stampa_lista(pFile,lis->next);
}

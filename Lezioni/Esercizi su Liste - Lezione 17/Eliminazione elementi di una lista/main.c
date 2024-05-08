/*
Riprendere dall'esercizio Costruzione di una lista la funzione

coppia *leggi_coppia(FILE *f)

che legge una coppia dal file di testo f (usare fscanf per leggere i due interi) e restituisce un puntatore alla coppia letta. La funzione deve restituire NULL se la lettura dal file fallisce.

Scrivere una funzione

coppia *inserisci_coda(coppia *lis, coppia *el)

che data una lista lis e un nuovo elemento el inserisce l'elemento el in fondo alla lista.

Scrivere una funzione

coppia *cancella_somma_dispari(coppia *lis)

che data una lista lis elimina e dealloca tutti gli elementi la cui somma delle componenti è dispari.
La funzione deve restituire il puntatore al primo elemento della lista ottenuta dopo la cancellazione.

Scrivere poi un main che legge il nome di un file di testo dalla linea di comando. 
Successivamente apre il file e, partendo da una lista vuota e chiamando ripetutamente leggi_coppia 
e inserisci_coda, legge gli elementi dal file e li inserisce nella lista. 
Si osservi che nella lista gli elementi saranno nello stesso ordine che nel file di output.

Il main deve successivamente invocare la funzione cancella_somma_dispari per eliminare e 
deallocare dalla lista le copie la cui somma è dispari. 
Infine, gli elementi della lista così ottenuta devono essere stampati su stdout invocando la funzione 
scrivi_lista (già disponibile nel codice sorgente); 
successivamente il programma deve deallocare tutta la memoria utilizzata 
(usare valgrind per la verifica) e terminare.

Ad esempio, se viene passato il nome del file test1 che al suo interno contiene

1 1
2 1
2 2

su stdout si deve ottenere il seguente output

1 1
2 2
Totale: 2 elementi

Dopo che avete scritto e testato il vostro programma, dando il comando verifica.py sulla linea di comando verrà controllata la correttezza del vostro programma sui file di test. Questa verifica richiede che l'eseguibile si chiami main e che su stdout venga scritto solamente il risultato finale. 
*/

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct cop {
   int primo;
   int secondo;
   struct cop *next; 
 } coppia;
 
coppia *crea_coppia(int p,int s);

coppia *leggi_coppia(FILE *f);

//------------------------------------------------------------------------------------------------------
coppia *cancella_somma_dispari(coppia *lis);

coppia *inserisci_coda(coppia *lis, coppia *el);
//------------------------------------------------------------------------------------------------------

void dealloca_lista(coppia *lis);

void termina(const char messaggio[]);

// NON modificare questa funzione
// scrive gli elementi di una lista di coppie nel file f
void scrivi_lista(coppia *lis, FILE *f)
{
	int tot=0;
  while(lis!=NULL) {
	  fprintf(f,"%d %d\n",lis->primo, lis->secondo);
		lis = lis->next;
		tot++;
	}
	fprintf(f,"Totale: %d elementi\n",tot);
}

int main(int argv, char *argc[]){
	
	if(argv != 2)
		termina("Uso: nome_file_contenente_coppie");
	
	FILE *pFile = fopen(argc[1],"rt");
	
	if(pFile==NULL)
		termina("Errore fopen");
	
	coppia *el;
	coppia *lis = NULL;
	while((el = leggi_coppia(pFile)) != NULL){
		lis = inserisci_coda(lis,el);	
	}
	
	scrivi_lista(lis,stdout);
	
	lis = cancella_somma_dispari(lis);
	
	scrivi_lista(lis,stdout);
	
	dealloca_lista(lis);
	
	fclose(pFile);
	
	return 0;
	
}

coppia *cancella_somma_dispari(coppia *lis){
	
	if(lis==NULL)
		return lis;
		
	assert(lis!=NULL);
	
	//il primo elemento della lista e' dispari
	if((lis->primo+lis->secondo)%2 != 0){
		
		coppia *tmp = lis->next;
	
		free(lis);
		
		if(tmp != NULL)
			lis = cancella_somma_dispari(tmp);
		else
			return tmp;	//tmp = NULL
	}
	
	coppia *prec = lis;
	coppia *el = lis->next;
	
	while(el != NULL){
		
		if((el->primo+el->secondo)%2 != 0){
			
			prec->next = el->next;
			free(el);
			el = prec->next;
		}
		else{
			prec = el;
			el = el->next;
		}
	}

	prec->next = NULL;

	return lis;
}

void dealloca_lista(coppia *lis){
	
	coppia *el = lis;
	while(el != NULL){
		coppia *tmp = el->next;
		free(el);
		el = tmp;
	}
}

coppia *inserisci_coda(coppia *lis, coppia *el){
	
	if(lis==NULL)
		return el;
	
	coppia *prec = lis;
	coppia *ell = lis->next;
	
	while(ell != NULL){
			prec = ell;
			ell = ell->next; 
	}
	
	prec->next = el;
	
	return lis;
}

coppia *leggi_coppia(FILE *pFile){
	
	int num1;
	int num2;
	
	int e = fscanf(pFile,"%d %d",&num1,&num2);
	
	if(e != 2)
		return NULL;
		
	coppia *el = crea_coppia(num1,num2);
	
	return el;	
}

coppia *crea_coppia(int p,int s){
		
	coppia *el = malloc(sizeof(coppia));
	
	if(el==NULL)
		termina("Errore malloc");
		
	el->primo = p;
	el->secondo = s;
	el->next = NULL;
	
	return el;
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]);

typedef struct citta{
	char *nome;
	int popolazione;
	//non c'e' piu' bisogno del campo next essendo in un array di puntatori di citta'.
}citta;

int leggi_array_ordinato_file(citta *a[],int nmax,FILE *pFile);

citta *citta_crea(char nome[],int popolazione);

//a lo posso scrivere: **a oppure *a[], sono due modi equivalenti per scrivere la stessa cosa.
void array_stampa(citta *a[],int n,FILE *pFile);

void citta_stampa(citta *a,FILE *pFile);

citta *leggi_citta_da_file(FILE *pFile);

void inserisci_citta_ordinata(citta *a[],int n,citta *c);

void citta_distruggi(citta *c);

//DA SCRIVERE L'ORDINAMENTO DEL VETTORE PASSANDOGLI LA FUNZIONE CON CUI ORDINARE L'ARRAY
//ES. Popolazione o Nome.

int leggi_array_file(citta *a[],int nmax,FILE *pFile);

//non restituisce nulla perche' deve soltanto spostare gli elementi all'interno del array
void ordina_sort_nome(citta *a[],int n);

//------------------------------------------------------------------------------------------------
// Esercizio per casa:
// restituisce la somma delle popolazioni di tutte le citta nell'array
int somma_pop_array_citta(citta *a[], int n)
{
	int somma = 0;
  
	for(int i = 0;i<n;i++)
		somma += a[i]->popolazione;
	
	return somma;
}

// Esercizio per casa:
// se esiste una citta di nome m restituisce un puntatore ad essa,
// se non esiste restituisce NULL
citta *cerca_citta_nome(citta *a[], int n, char *m)
{
	for(int i = 0;i<n;i++){
		if(strcmp(a[i]->nome,m)==0){
			return a[i];
		}	
	}
	return NULL;
}
//-------------------------------------------------------------------------------------------------
int main(int argc,char *argv[]){

	//*a[] non e' ammesso, e' ammesso solo durante l'intestazione di una funzione.
	citta **a = malloc(sizeof(citta *)*10);
	
	if(a==NULL)
		termina("Errore malloc");
	
	FILE *pFile1 = fopen(argv[1],"rt");
	
	if(pFile1 == NULL)
		termina("Errore fopen 1");
	
	int n = leggi_array_ordinato_file(a,10,pFile1);
	fclose(pFile1);
	
	array_stampa(a,n,stdout);
	
	for(int i = 0;i<n;i++)
		citta_distruggi(a[i]);
	free(a);
	
	citta **b = malloc(sizeof(citta *)*10);
	
	if(b==NULL)
		termina("Errore malloc");
	
	FILE *pFile2 = fopen(argv[2],"rt");
	
	if(pFile2 == NULL)
		termina("Errore fopen 2");
	
	n = leggi_array_file(b,10,pFile2);
	fclose(pFile2);
	
	array_stampa(b,n,stdout);
	
	ordina_sort_nome(b,n);
	
	array_stampa(b,n,stdout);
	
	int somma_pop = somma_pop_array_citta(b,n);
	
	fprintf(stdout,"Somma popolazione array b: %d\n",somma_pop);
	
	citta *c1 = cerca_citta_nome(b,n,"Central City");
	if(c1!=NULL)
		fprintf(stdout,"Cerca citta' Central City: %d\n",c1->popolazione);
	
	
	citta *c2 = cerca_citta_nome(b,n,"Lucca");
	if(c2!=NULL)
		fprintf(stdout,"Cerca citta' Lucca: %d\n",c2->popolazione);
	
	for(int i = 0;i<n;i++)
		citta_distruggi(b[i]);
	free(b);
	
	return 0;
}

//svolgo l'insertion sort, sposto gli elementi che si trovano all'interno dell'array
void ordina_sort_nome(citta *a[],int n){
	
	for(int i =1;i<n;i++){
		citta *c = a[i];
		inserisci_citta_ordinata(a,i,c);
	}
}

//legge al massimo nmax citta dal file pFile e le scrive in a[]
//restituisce il numero di citta' effettivamente lette.
int leggi_array_ordinato_file(citta *a[],int nmax,FILE *pFile){
	
	//array a gia' allocato, puo' contenere nmax-1 elementi.
	//l'elemento nmax (ultimo) deve essere libero per la funzione inserisci_citta_ordinata. 
	for(int i = 0;i<nmax;i++){
		citta *c = leggi_citta_da_file(pFile);
		
		if(c==NULL)
			return i;
		else
			inserisci_citta_ordinata(a,i,c);
	}
	//esco dal ciclo for quando ho inserito tutti gli elementi in a
	return nmax;
}

int leggi_array_file(citta *a[],int nmax,FILE *pFile){
	
	//array a gia' allocato, puo' contenere nmax-1 elementi.
	//l'elemento nmax (ultimo) deve essere libero per la funzione inserisci_citta_ordinata. 
	for(int i = 0;i<nmax;i++){
		citta *c = leggi_citta_da_file(pFile);
		
		if(c==NULL)
			return i;
		else
			a[i] = c;
	}
	//esco dal ciclo for quando ho inserito tutti gli elementi in a
	return nmax;
}

//inserisci lla citta c nell'array a[] mantenendo l'ordine lessicografico.
//si suppone che la posizione a[n] esista e sia libera.
void inserisci_citta_ordinata(citta *a[],int n,citta *c){
	
	//parto dal fondo, scorro le citta da destra verso sinistra.
	for(int i = n-1;i>=0;i--){
		
		//il nome di c e' piu' piccolo del nome di a[i]
		if(strcmp(c->nome,a[i]->nome) < 0)
			a[i+1] = a[i];
		//in entrambi i casi vado a sovrascrivere a[i+1]
		else{
			a[i+1] = c;
			return;		//una volta che ho piazzato la mia citta c nel array devo concludere
		}
	}
	
	//esco dal ciclo for quando il nome della citta' e' il piu' piccolo di tutte le citta
	a[0] = c;
	return; 
}

void array_stampa(citta *a[],int n,FILE *pFile){

	for(int i = 0;i<n;i++)
		citta_stampa(a[i],pFile);
	fprintf(pFile,"\n");

}

void citta_stampa(citta *a,FILE *pFile){
	fprintf(pFile,"%s: %d\n",a->nome,a->popolazione);
}

citta *leggi_citta_da_file(FILE *pFile){
	
	char *s = NULL;
	size_t dims = 0;
	
	//la getline legge dall'inizio della riga fino allo \n
	int e = getline(&s,&dims,pFile);
	
	if(e == -1){
		free(s);
		return NULL;
	}
	
	char *p = NULL;
	size_t dimp = 0;
	
	e = getline(&p,&dimp,pFile);
	
	if(e == -1){
		free(s);
		free(p);
		return NULL;
	}
	
	//sovrascrivo \n con \0
	if(s[strlen(s)-1] == '\n')
		s[strlen(s)-1] = '\0';
	
	citta *c = citta_crea(s,atoi(p));
	
	free(s);
	free(p);
	
	return c;
	
}

citta *citta_crea(char nome[],int popolazione){

	citta *c = malloc(sizeof(citta));
	
	if(c==NULL)
		termina("Errore malloc");

	c->nome = strdup(nome);
	c->popolazione = popolazione;

	return c;  
}

void citta_distruggi(citta *c){
	
	free(c->nome);
	free(c);
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

typedef struct citta{
	char *nome;
	int popolazione;
	struct citta *next;
}citta;

citta *citta_crea(char nome[],int popolazione);

citta *leggi_citta_da_file(FILE *pFile);

void termina(const char messaggio []);

citta *aggiungi_citta_in_testa(citta *lis,citta *el);

int conta_citta_in_range(citta *lista, int minp, int maxp);
int conta_citta_in_range_ric(citta *lista, int minp, int maxp);

int somma_pop_lista_citta(citta *lista);
int somma_pop_lista_citta_ric(citta *lista);

citta *cerca_citta_nome(citta *lista, char *n);
citta *cerca_citta_nome_ric(citta *lista, char *n);

citta *cancella_citta(citta *lis, char *n);

citta *leggi_lista_da_file(FILE *pFile);

void stampa_lista(citta *lis,FILE *pFile){
	
	citta *el = lis;
	while(el != NULL){
		fprintf(pFile,"%s: %d\n",el->nome,el->popolazione);
		el = el->next;
	}
	fprintf(pFile,"\n");

	return;
}

int main(int argc,char *argv[]){

	if(argc != 2)
		termina("Uso: nome_del_file");
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile == NULL)
		termina("Errore fopen");
		
	citta *lis = leggi_lista_da_file(pFile);
	
	stampa_lista(lis,stdout);
	
	fprintf(stdout,"Somma popolazione lista, funzione ric: %d\n",somma_pop_lista_citta_ric(lis));
	fprintf(stdout,"Somma popolazione lista, funzione iterativa: %d\n\n",somma_pop_lista_citta(lis));
	
	fprintf(stdout,"Citta con pop tra %d e %d, funzione ric: %d\n",44000,1500000,conta_citta_in_range_ric(lis,44000,1500000));
	fprintf(stdout,"Citta con pop tra %d e %d, funzione iterativa: %d\n\n",44000,1500000,conta_citta_in_range(lis,44000,1500000));
	
	citta *c1 = cerca_citta_nome(lis,"Gotham City");
	citta *c2 = cerca_citta_nome_ric(lis,"Metropolis");
	
	fprintf(stdout,"->%s: %d\n",c1->nome,c1->popolazione);
	fprintf(stdout,"->%s: %d\n\n",c2->nome,c2->popolazione);
	
	lis = cancella_citta(lis,"Gotham City");
	lis = cancella_citta(lis,"Metropolis");
	lis = cancella_citta(lis,"Star City");
	lis = cancella_citta(lis,"Gondor");
	
	stampa_lista(lis,stdout);
	
	return 0;
}

citta *leggi_lista_da_file(FILE *pFile){
	
	citta *el;
	citta *lis = NULL;
	while((el = leggi_citta_da_file(pFile)) != NULL){
		lis = aggiungi_citta_in_testa(lis,el);
	}
	
	return lis;
}

citta *citta_crea(char nome[],int popolazione){

	citta *c = malloc(sizeof(citta));
	
	if(c==NULL)
		termina("Errore malloc");
	
	//ho due zone separate, e' piu' sicuro.	
	c->nome = strdup(nome);
	
	c->popolazione = popolazione;
	c->next = NULL;
	
	return c;  
}

citta *aggiungi_citta_in_testa(citta *lis,citta *el){

	el->next = lis;
	return el;
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

// Esercizio per casa:
// dealloca tutti gli elementi della lista
// deallocare la memoria usata dalla lista chiamando 
// citta_distruggi su ogni elemento
void citta_distruggi(citta *c){
	
	free(c->nome);
	free(c);
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

int somma_pop_lista_citta(citta *lista)
{
	int somma = 0;
	
	citta *el = lista;
	while(el != NULL){
		somma += el->popolazione;
		el = el->next;
	}
	
	return somma;
}

// Esercizio per casa:
// restituisce la somma delle popolazioni di tutte le citta nella lista
// provare a scrivere una versione ricorsiva 
int somma_pop_lista_citta_ric(citta *lista)
{
	if(lista==NULL)
		return 0;
	else
		return lista->popolazione + somma_pop_lista_citta_ric(lista->next); 
}

// Esercizio per casa:
// restituisce il numero di citta' con popolazione tra minp e maxp 
int conta_citta_in_range(citta *lista, int minp, int maxp)
{
	int somma = 0;
  
	citta *el = lista;
	while(el != NULL){
		if(el->popolazione > minp && el->popolazione < maxp)
			somma++;
		el = el->next;
	}
  
  return somma;
}

int conta_citta_in_range_ric(citta *lista, int minp, int maxp)
{
	if(lista == NULL)
		return 0;
	
	if(lista->popolazione>minp && maxp>lista->popolazione)
		return 1+conta_citta_in_range(lista->next,minp,maxp);
	else
		return 0+conta_citta_in_range(lista->next,minp,maxp);
}

// Esercizio per casa:
// se esiste una citta di nome n restituisce un puntatore ad essa,
// se non esiste restituisce NULL
// per confrontare il nome n con il nome della citta a cui punta c
//  strcmp(n,c->nome) se ==0 le due stringhe sono uguali 
citta *cerca_citta_nome(citta *lista, char *n)
{
	citta *el = lista;
	while(el!=NULL){
		if(strcmp(el->nome,n)==0)
			return el;
		el = el->next;
	}
	return NULL;
}

citta *cerca_citta_nome_ric(citta *lista, char *n)
{
	if(lista==NULL)
		return lista;
	
	if(strcmp(lista->nome,n)==0)
		return lista;
	else 
		return cerca_citta_nome_ric(lista->next,n);
}

// Esercizio per casa:
// cancella eventuale citta' di nome n
// restituisce il puntatore alla lista modificata
// vedere l'analoga funzione fatta per la lista di interi
// non dimenticarsi di chiamare citta_distruggi() per deallocare
citta *cancella_citta(citta *lis, char *n)
{
	if(lis==NULL)
		return lis;
	
	if(strcmp(lis->nome,n)==0){
		
		citta *tmp = lis->next;
		
		citta_distruggi(lis);
		
		if(tmp != NULL)
			return cancella_citta(lis->next,n);
		else 
			return tmp;
	}
	
	citta *prec = lis;
	citta *el = lis->next;
	while(el!=NULL){
		if(strcmp(el->nome,n) == 0){
			prec->next = el->next;
			citta_distruggi(el);
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


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

citta *leggi_lista_da_file(FILE *pFile);

citta *aggiungi_citta_ordinata_funz(citta *lis,citta *el,int (*confronta)(citta*,citta*));
int confronta_nome(citta *a,citta *b);
int confronta_popolazione(citta *a,citta *b);

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
	
	return 0;
}

citta *aggiungi_citta_ordinata_funz(citta *lis,citta *el,int (*confronta)(citta*,citta*)){

	if(lis == NULL){
		el->next = NULL;
		return el;
	}
	
	if(confronta(el,lis)<0){
		el->next = lis;
		return el;
	}
	
	lis->next = aggiungi_citta_ordinata_funz(lis->next,el,confronta);
	return lis;
}

//restituisce:
//->0 se sono uguali
//->1 se a > b
//->-1 se a < b
int confronta_nome(citta *a,citta *b){
	return strcmp(a->nome,b->nome);
}

int confronta_popolazione(citta *a,citta *b){
	if(a->popolazione>b->popolazione)
		return 1;
	else if(a->popolazione<b->popolazione)
		return -1;
	else 
		return 0;
}

citta *leggi_lista_da_file(FILE *pFile){
	
	citta *el;
	citta *lis = NULL;
	while((el = leggi_citta_da_file(pFile)) != NULL){
		//lis = aggiungi_citta_ordinata_funz(lis,el,confronta_nome);
		lis = aggiungi_citta_ordinata_funz(lis,el,confronta_popolazione);
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

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}


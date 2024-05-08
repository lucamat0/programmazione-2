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

citta *leggi_lista_da_file(FILE *pFile);

citta *aggiungi_citta_ordinata_pop_ric(citta *lis,citta *c);

citta *aggiungi_citta_ordinata_nome_ric(citta *lis,citta *c);

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

citta *aggiungi_citta_ordinata_nome_ric(citta *lis,citta *c){

	if(lis==NULL){
		c->next = NULL;
		return c;
	}
	
	if(strcmp(c->nome,lis->nome)<0){
		c->next = lis;
		return c;
	}
	
	lis->next = aggiungi_citta_ordinata_nome_ric(lis->next,c);
	return lis;
	
}

citta *aggiungi_citta_ordinata_pop_ric(citta *lis,citta *c){

	if(lis==NULL){
		c->next = NULL;
		return c;
	}
	
	if(c->popolazione<lis->popolazione){
		c->next = lis;
		return c;
	}
	
	lis->next = aggiungi_citta_ordinata_pop_ric(lis->next,c);
	return lis;
}

citta *leggi_lista_da_file(FILE *pFile){
	
	citta *el;
	citta *lis = NULL;
	while((el = leggi_citta_da_file(pFile)) != NULL){
		//lis = aggiungi_citta_ordinata_pop_ric(lis,el);
		lis = aggiungi_citta_ordinata_nome_ric(lis,el);
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


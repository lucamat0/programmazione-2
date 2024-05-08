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

citta *aggiungi_citta_ordinata_pop_ric(citta *lis,citta *c);

citta *merge_liste(citta *lis1,citta *lis2);

citta *merge_liste_ric(citta *lis1,citta *lis2);

void distruggi_lista(citta *lis);

void stampa_lista(citta *lis,FILE *pFile){
	
	citta *el = lis;
	while(el != NULL){
		fprintf(pFile,"%s: %d\n",el->nome,el->popolazione);
		el = el->next;
	}
	fprintf(pFile,"\n");

	return;
}

void distruggi_lista(citta *lis){

	if(lis==NULL)
		return;
		
	distruggi_lista(lis->next);
	
	free(lis->nome);
	free(lis);
	
	return;
}

int main(int argc,char *argv[]){

	if(argc != 3)
		termina("Uso: nome_del_file");
	
	FILE *pFile1 = fopen(argv[1],"rt");
	
	if(pFile1 == NULL)
		termina("Errore fopen");
		
	citta *lis1 = leggi_lista_da_file(pFile1);
	
	stampa_lista(lis1,stdout);
	
	fclose(pFile1);
	
	FILE *pFile2 = fopen(argv[2],"rt");
	
	if(pFile2==NULL)
		termina("Errore fopen");
		
	citta *lis2 = leggi_lista_da_file(pFile2);
	
	stampa_lista(lis2,stdout);
	
	fclose(pFile2);
	
	//eseguiamo il merge tra le due liste.
	citta *lis = merge_liste(lis1,lis2);
	
	stampa_lista(lis,stdout);
	
	distruggi_lista(lis);
	
	return 0;
}

//esegue il merge di due liste ordinate.
citta *merge_liste(citta *lis1,citta *lis2){

	//punta al primo elemento della lista
	citta *lis = NULL;
	
	//punta all'ultimo elemento della lista
	citta *coda = NULL;
	
	citta *prossimo;
	
	//copro il caso in cui una delle due liste e' vuota
	if(lis1==NULL)	//se la prima lista e' vuota il risultato e' la lista 2
		return lis2;
	else if(lis2==NULL)	//se la seconda lista e' vuota il risultato e' la lista 1
		return lis1;
		
	while(lis1 != NULL && lis2 != NULL){
		//devo prendere lis1
		if(lis1->popolazione<lis2->popolazione){
			//il prossimo elemento della lista lis e' lis1
			prossimo = lis1;
			
			//faccio avanzare lis1
			lis1 = lis1->next;
		}
		else{
			prossimo = lis2;
			lis2 = lis2->next;
		}
		//viene eseguito solo alla prima iterazione del while
		if(lis == NULL)
			lis = prossimo;
		//viene eseguito tutte le altre volte.
		else
			coda->next = prossimo;
			
		prossimo->next = NULL;
		coda = prossimo;
	}
	
	assert(lis != NULL && coda != NULL);
	
	//una delle due liste, quando si esce dal ciclo while e' finita.
	if(lis1 != NULL)
		coda->next = lis1;
	else if(lis2 != NULL)
		coda->next = lis2;
	//restituisco il primo elemento della lista risultato
	return lis;
}

/* NON FUNZIONA!
//versione ricorsiva del merge di liste
citta *merge_liste_ric(citta *lis1,citta *lis2){
	
	if(lis1 != NULL)
		return lis2;
	else if(lis2 != NULL)
		return lis1;
		
	citta *lis = NULL;
	if(lis1->popolazione<lis2->popolazione){
		lis = lis1;
		lis1 = lis1->next;
	}
	else{
		lis = lis2;
		lis2 = lis2->next;
	}
	
	lis->next = merge_liste_ric(lis1,lis2);
	
	return lis;
}
*/
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
		
		lis = aggiungi_citta_ordinata_pop_ric(lis,el);
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


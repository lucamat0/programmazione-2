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

citta *citta_crea(char nome[],int popolazione);

//a lo posso scrivere: **a oppure *a[], sono due modi equivalenti per scrivere la stessa cosa.
void array_stampa(citta *a[],int n,FILE *pFile);

void citta_stampa(citta *a,FILE *pFile);

citta *leggi_citta_da_file(FILE *pFile);

void citta_distruggi(citta *c);

int leggi_array_file(citta *a[],int nmax,FILE *pFile);

int ordina_per_popolazione(const citta **c1,const citta **c2);

int ordina_per_nome(const citta **c1,const citta **c2);

int main(int argc,char *argv[]){

	//*a[] non e' ammesso, e' ammesso solo durante l'intestazione di una funzione.
	citta **a = malloc(sizeof(citta *)*10);
	
	if(a==NULL)
		termina("Errore malloc");
	
	FILE *pFile1 = fopen(argv[1],"rt");
	
	if(pFile1 == NULL)
		termina("Errore fopen 1");
	
	int n = leggi_array_file(a,10,pFile1);
	fclose(pFile1);
	
	array_stampa(a,n,stdout);
	
	//ordino le citta' per popolazione: crescente
	qsort(a,n,sizeof(citta*),(__compar_fn_t)ordina_per_popolazione);
	
	array_stampa(a,n,stdout);
	
	//ordino le citta' per nome: crescente
	qsort(a,n,sizeof(citta*),(__compar_fn_t)ordina_per_nome);
	
	array_stampa(a,n,stdout);	
	
	for(int i = 0;i<n;i++)
		citta_distruggi(a[i]);
	free(a);
	
	return 0;
}

int ordina_per_nome(const citta **c1,const citta **c2){

	return strcmp((*c1)->nome,(*c2)->nome);
}

int ordina_per_popolazione(const citta **c1,const citta **c2){
	
	if((*c1)->popolazione<(*c2)->popolazione)
		return -1;
	else if((*c1)->popolazione>(*c2)->popolazione)
		return 1;
	else
		return 0;
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


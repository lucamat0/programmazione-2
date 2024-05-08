#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp
#include <ctype.h>		//posso utilizzare la funzione 

/*
3a) Si utilizzi la struttura

typedef strict elx {
  char *s;
  struct elx *next;
} stringa;
per rappresentare un elemento di una lista di stringhe. Si scriva una funzione

stringa *leggieordina(FILE *f)

che legge, mediante fscanf, le stringhe contenute nel file f e restituisce una lista di tali stringhe ordinate per numero crescente di lettere maiuscole in esse contenute. 
Di conseguenza se il file contenesse

CIAO pizza
Milano OK
la lista restituita dovrebbe contenere nell'ordine le stringhe:

pizza Milano OK CIAO
*/

typedef struct elx {
  char *s;
  struct elx *next;
} stringa;

stringa *leggieordina(FILE *f);

stringa *crea_elemento(char s[]);

stringa *inserimento_ordinato(stringa *lis,stringa *el);

void stampa_lista(stringa *lis);

int contaM(const char *s);

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

/*
3b) Si scriva un main che legge il nome di un file dalla line di comando, apre il relativo file passandolo a leggieordina 
e stampa gli elementi dalla lista così ottenuta. Successivamente dealloca tutta la memoria utilizzata dalla lista.
*/

void dealloca_lista(stringa *lis);

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: nome_file");
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile==NULL)
		termina("Errore fopen");
	
	
	stringa *lis = leggieordina(pFile);
	
	stampa_lista(lis);
	
	fclose(pFile);
	
	dealloca_lista(lis);
	
}

void dealloca_lista(stringa *lis){
	
	if(lis==NULL)
		return;
		
	dealloca_lista(lis->next);
	
	free(lis->s);
	free(lis);
	
}

void stampa_lista(stringa *lis){
	
	if(lis==NULL)
		return;
		
	fprintf(stdout,"%s\n",lis->s);
		
	stampa_lista(lis->next);
	
	return;
}

int contaM(const char *s){
	int conta = 0;
	for(int i = 0;i<strlen(s);i++){
		if(isupper(s[i])!=0)
			conta++;
	}
	return conta;

}

stringa *leggieordina(FILE *pFile){
	
	char s1[100];
	char s2[100];
	stringa *lis = NULL;
	stringa *el;
	while((fscanf(pFile,"%99s %99s",s1,s2))!= EOF){
		
		el = crea_elemento(s1); 
		lis = inserimento_ordinato(lis,el);
		el = crea_elemento(s2); 
		lis = inserimento_ordinato(lis,el);
	}
	
	return lis;
}


stringa *inserimento_ordinato(stringa *lis,stringa *el){
	
		if(lis==NULL){
			el->next = NULL;
			return el;
		}
		
		stringa *prec = lis;
		stringa *ell = lis->next;
		while(ell!=NULL){
			
			if(contaM(ell->s)>=contaM(el->s)){
				
				prec->next = el;
				el->next = ell;
				
				return lis;
			}
			prec = ell;
			ell = ell->next;
		}
		
		prec->next = el;
		el->next = NULL;
		
		return lis;
}


stringa *crea_elemento(char s1[]){

	stringa *mys = malloc(sizeof(stringa));
	
	if(s1==NULL)
		termina("Errore malloc");
		
	mys->s = strdup(s1);
	mys->next = NULL;
	
	return mys;
}

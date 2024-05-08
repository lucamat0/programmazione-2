#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

//Permette di rappresentare una lista di stringhe.
typedef struct par {
  char *stringa;
  struct par *next; 
} parola;

//data una stringa s crea una lista di stringhe ordinata lessicograficamente contenente i token 
//restituiti dalla funzione strtok usando come delimitatore il carattere :. 
//Ad esempio, se la stringa s contiene casa:telo-mare:albero::sedia deve essere restituita la 
//lista contenente nell'ordine le stringhe albero, casa, sedia, telo-mare.
parola *crea_lista(char *s);
parola *crea_elemento(char *s);

parola *inserimentoordinato(parola *lis,parola *el);

//data una lista di stringhe elimina e dealloca gli elementi contenenti una stringa che termina con 
//il carattere c.
parola *elimina_sefinale(parola *, char c);

void stampa_lista(parola *lis);

int lung_stringa(char *s){
	return strlen(s);
}

void dealloca_lista(parola *lis);

int main(int argc,char *argv[]){
	
	if(argc!=3)
		termina("Uso: stringa_1 caratter_semifinale");
	
	parola *lis = crea_lista(argv[1]);
	
	puts("--- Lista Ordinata ---");
	stampa_lista(lis);
	puts("--- ---");
	
	char *s = argv[2];
	for(int i=0;i<strlen(s);i++)
		lis = elimina_sefinale(lis,s[i]);
	
	puts("--- Lista senza lettera finale a ---");
	stampa_lista(lis);
	puts("--- ---");
	
	//stampa su stderr le lunghezze di tutte le stringhe che si trovano ancora in lis
	parola *el = lis;
	while(el!=NULL){
		fprintf(stderr,"%d\t",lung_stringa(el->stringa));
		el = el->next;
	}
	fprintf(stderr,"\n");
	 
	//dealloca tutti gli elementi rimasti in lis e termina; verificare con valgrind che tutta 
	//la memoria venga correttamente deallocata.
	dealloca_lista(lis);
	return 0;
}

void dealloca_lista(parola *lis){
	
	if(lis==NULL)
		return;
	
	dealloca_lista(lis->next);
	free(lis->stringa);
	free(lis);
}

void stampa_lista(parola *lis){

	if(lis==NULL)
		return;
	
	fprintf(stdout,"%s\n",lis->stringa);
	stampa_lista(lis->next);
	
	return;
}

parola *elimina_sefinale(parola *lis, char c){
	
	if(lis->stringa[strlen(lis->stringa)-1] == c){
		parola *tmp = lis->next;
		free(lis->stringa);
		free(lis);
		
		return elimina_sefinale(tmp,c);
	}
	
	parola *prec = lis;
	parola *el = lis->next;
	
	while(el!=NULL){
		if(el->stringa[strlen(el->stringa)-1] == c){
			prec->next = el->next;
			
			free(el->stringa);
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

parola *crea_lista(char *s){
	
	assert(s!=NULL);
	
	char *t = strtok(s,":. ");
	
	parola *lis = NULL;
	parola *el = crea_elemento(t);
	lis = inserimentoordinato(lis,el);
	
	while((t = strtok(NULL,":. "))!=NULL){
		
		parola *el = crea_elemento(t);
		lis = inserimentoordinato(lis,el);
	}
	
	return lis;
}

parola *inserimentoordinato(parola *lis,parola *el){
	
	if(lis==NULL){
		el->next = NULL;
		return el;
	}
	else if(strcmp(el->stringa,lis->stringa)<0){
		el->next = lis;
		return el;
	}
	
	parola *prec = lis;
	parola *ell = lis->next;
	while(ell!=NULL){
		if(strcmp(ell->stringa,el->stringa)>0){
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

parola *crea_elemento(char *s){
	
	parola *p = malloc(sizeof(parola));
	
	p->stringa = strdup(s);
	p->next = NULL;
	
	return p;
}

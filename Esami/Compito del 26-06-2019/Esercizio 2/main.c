/*
2) Scrivere un programma che crea un array contenente una copia delle 
stringhe passate sulla linea di comando e una copia di tali stringhe 
ribaltate (ad esempio "Sole" -> "eloS"). Questo array di stringhe deve 
essere visualizzato e poi ordinato ignorando la distinzione tra 
maiuscole e minuscole, utilizzando la funzione qsort() combinata a 
strcasecmp(). 
L'array ordinato deve essere nuovamente visualizzato e successivamente 
completamente deallocato (usare valgrind per la verifica). 
Esempio, scrivendo:

esercizio2 Sole sale sTalle
deve essere prima visualizzato l'array non ordinato

Sole sale sTalle eloS elas ellaTs
e successivamente l'array ordinato

elas
ellaTs
eloS
sale
Sole
sTalle

Si noti che se non si ignora la distinzione tra maiuscole e minuscole 
le ultime 3 parole sarebbero ordinate Sole sTalle sale perchè in ASCII 
le maiuscole vengono prima delle minuscole.
*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

char *inserisci_stringa(char s[]);
char *ribalta_stringa(char s[]);

void stampa_array(char *s[],int dim);

int ordina_per_nome(const char **c1, const char **c2);

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[]){
	
	if(argc == 1)
		termina("Uso: string1 string2 ... stringN");
		
	int dim = (argc-1)*2;
	char **myVectorS = malloc(sizeof(char **)*dim);
	
	if(myVectorS==NULL)
		termina("Errore malloc");
	
	for(int i=0;i<(dim/2);i++){
		myVectorS[i] = inserisci_stringa(argv[i+1]);
		myVectorS[(dim-1)-i] = ribalta_stringa(argv[i+1]);
	}
	
	fprintf(stdout,"--- ---\n");
	stampa_array(myVectorS,dim);
	fprintf(stdout,"--- ---\n");
	
	qsort(myVectorS,dim,sizeof(char **),(__compar_fn_t)ordina_per_nome);
	
	fprintf(stdout,"--- ---\n");
	stampa_array(myVectorS,dim);
	fprintf(stdout,"--- ---\n");
	
	for(int i=0;i<dim;i++)
		free(myVectorS[i]);
	free(myVectorS);
	return 0;
}

int ordina_per_nome(const char **c1, const char **c2){
	return strcmp(*c1,*c2);
}

void stampa_array(char *s[],int dim){
	
	for(int i=0;i<dim;i++)
		fprintf(stdout,"%s \n",s[i]);
}

char *inserisci_stringa(char s[]){

	return strdup(s);
}

char *ribalta_stringa(char s[]){
	
	int dim = strlen(s);
	char *c = malloc(sizeof(char *)*dim);
	
	if(c==NULL)
		termina("Errore malloc");
	
	for(int i=0;i<dim;i++){
		c[i] = s[dim-1-i];
	}
	
	return c;
} 

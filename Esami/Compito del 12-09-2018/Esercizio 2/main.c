#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp
#include <ctype.h>		//posso utilizzare la funzione 

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

/*
2a) Scrivere una funzione

int contaM(char *s)
che data una stringa s conta il numero di lettere maiuscole in essa contenute. 
Si usi la funzione isupper per determinare se un dato carattere è maiuscolo.
*/

int contaM(const char *s);

/*
2b) Scrivere una funzione

ordina_maiuscole(char *a[], int n)
che, utilizzano la funzione di libreria qsort, ordina un array a[] di n stringhe in ordine di numero crescente di lettere maiuscole in esse contenute. Ad esempio, se

a = {"CIAO", "Milano", "OK", "pizza"}
*/

int ordina_maiuscole(const char **s1,const char **s2);
void stampa_stringhe(char a[],FILE *pFile);

int main(int argc,char *argv[]){
	
	if(argc<2)
		termina("Uso: x1 x2 ... xn");
	
	/*
	int conta = contaM("Ciao");
	fprintf(stdout,"conta: %d\n",conta);
	*/
	int dim = argc-1;
	char **a = malloc(sizeof(char *)*dim);
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<dim;i++)
		a[i] = strdup(argv[i+1]);
	
	for(int i = 0;i<dim;i++)
		stampa_stringhe(a[i],stdout);
	fprintf(stdout,"\n");
	
	qsort(a,dim,sizeof(char *),(__compar_fn_t)ordina_maiuscole);
	
	for(int i = 0;i<dim;i++)
		stampa_stringhe(a[i],stdout);
	fprintf(stdout,"\n");
	
	for(int i = 0;i<dim;i++)
		free(a[i]);
	free(a);
	
	return 0;
}

void stampa_stringhe(char a[],FILE *pFile){
	fprintf(pFile,"%s\n",a);
}

int ordina_maiuscole(const char **s1,const char **s2){
	
	if(contaM(*s1)<contaM(*s2))
		return -1;
	else if(contaM(*s1)>contaM(*s2))
		return 1;
	else 
		return 0;
	

}

int contaM(const char *s){
	int conta = 0;
	for(int i = 0;i<strlen(s);i++){
		if(isupper(s[i])!=0)
			conta++;
	}
	return conta;

}

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

/*
1a) Scrivere una funzione

int *ruota(int a[], int n)
che dato un array di interi a[] di n elementi alloca e restituisce un nuovo array di interi che contiene gli stessi 
elementi di a[] ma ruotati ciclicamente di un elemento verso sinistra. Ad esempio, se a = {2,3,5,7,11} la funzione deve 
restituire l'array {3,5,7,11,2}

*/

int *ruota_int(int a[], int n);

int *crea_array_int(int dim,int *b);

void stampa_array_int(int *a,int dim);

/*
1b) Scrivere una funzione

int **rotazioni(int a[], int n, int *righe)
che dato un array a[] di n elementi alloca e restituisce una matrice contenente tutte le rotazioni distinte di a[] 
(cioè tutti i vettori riga devono essere distinti). 
Ad esempio, se a = {2,3,5,7} la funzione deve restituire la matrice {{2,3,5,7},{3,5,7,2},{5,7,2,3},{7, 2, 3, 5}}. 
Se invece a = {2,3,2,3} la funzione deve restituire la matrice {{2,3,2,3}, {3,2,3,2}} 
(non ci sono altre righe perchè le rotazioni si ripetono). La funzione deve scrivere in *righe il numero di righe presenti 
nella matrice restituita. Suggerimento: scrivere una funzione ausiliaria che dati due array di n elementi restituisce true 
se essi hanno tutti gli elementi uguali.
*/
int **rotazioni_int(int a[], int n, int *righe);

/*
1c) Scrivere un main che costruisca un array contenente gli interi 
atoi(argv[1]), ..., atoi(argv[argc-1]), chiama la funzione rotazioni 
su di esso, stampa la matrice risultante e dealloca tutto lo spazio 
utilizzato dalla matrice
*/

/*
1d) Scrivere una funzione

char ***rotazioni_stringhe(char *a[], int n, int *righe)
che dato un array a[] contenente n stringhe restituisce una matrice di stringhe, 
le cui righe contengono tutte le rotazioni distinte degli elementi di a[]. 
Ad esempio, se a = {"mare", "sole", "amore"} la funzione deve restituire la matrice 
{{"mare", "sole", "amore"}, {"sole", "amore", "mare"}, {"amore", "mare", "sole"}}

se invece a = {"mare", "sole", "mare", "sole"} la funzione deve restituire

{{"mare", "sole", "mare", "sole"},
{"sole", "mare", "sole", "mare"}}

senza altre righe perché le rotazioni si ripetono. 
La funzione deve scrivere in *righe il numero di righe contenute nella matrice restituita.

Si suggerisce di realizzare questo esercizio seguendo la traccia dei punti a,b,c e quindi 
di scrivere una funzione

char **ruota_stringhe(char *a[], int n) 
che dato un array di stringhe restituisce un nuovo array contenente copie 
delle stringhe di a[] ruotate ciclicamente di una posizione verso sinistra; 
e un'altra funzione che dati due array di stringhe restituisce true se essi hanno tutti gli 
elementi uguali.
*/
char ***rotazioni_stringhe(char *a[], int n, int *righe);

void stampa_array(char *s[],int dim);
char **crea_array_str(int dim,char *a[]);
char **ruota_str(int n,char *s[]);

/*
1e) Rinominare il main precedente e scrivere un nuovo main che costruisca un array 
contenente una copia delle stringhe argv[1], ..., argv[argc-1], chiama la funzione 
rotazioni_stringhe su di esso, stampa la matrice risultante e dealloca tutto lo spazio 
utilizzato dalla matrice (controllare con valgrind).
*/
void dealloca_array(char *s[],int dim);

int main(int argc,char *argv[]){
	
	if(argc==1)
		termina("Uso: x1 x2 ... xn");
	/*
	int dim	= argc-1;
	int *a = malloc(sizeof(int)*dim);
	
	if(a==NULL)
		termina("Errore malloc");
	
	for(int i = 0;i<dim;i++)
		a[i] = atoi(argv[i+1]);
	
	//stampa_array_int(a,dim);
	
	//a = ruota_int(a,dim);
	
	//stampa_array_int(a,dim);
	
	int dimr;
	int **myVector = rotazioni_int(a, dim,&dimr);
	
	assert(dimr>0);
	
	fprintf(stdout,"--- Sto ruotando il vettore ---\n");
	for(int i=0;i<dimr;i++)
		stampa_array_int(myVector[i],dim);
	fprintf(stdout,"--- Fine rotazione vettore ---\n");
	
	for(int i=0;i<dimr;i++)
		free(myVector[i]);
	free(myVector);
	*/
	
	int dim = argc-1;
	char **s = malloc(sizeof(char *)*dim);
	
	if(s==NULL)
		termina("Errore malloc");
		
	for(int i = 0;i<dim;i++)
		s[i] = strdup(argv[i+1]);
	
	int righe;
	char ***myVectorS = rotazioni_stringhe(s,dim,&righe);
	
	assert(righe>0);
	
	fprintf(stdout,"--- Sto ruotando il vettore ---\n");
	for(int i=0;i<righe;i++)
		stampa_array(myVectorS[i],dim);
	fprintf(stdout,"--- Fine rotazione vettore ---\n");
	
	for(int i=0;i<righe;i++)
		dealloca_array(myVectorS[i],dim);
	free(myVectorS);
	
	return 0;
}

char ***rotazioni_stringhe(char *a[], int n, int *righe){

	char ***myVectorS = malloc(sizeof(char **)*n);
	
	if(myVectorS == NULL)
		termina("Errore malloc");
	
	int messi = 0;
	myVectorS[messi] = a;
	messi++;
	
	stampa_array(myVectorS[messi-1],n);
	
	bool find;
	if(n%2==0){
		find = true;
		for(int i=0;i<(n-2);i++)
			if(strcmp(a[i],a[i+2])!=0)
				find = false;
	}
	else
		find=false;
	
	for(int i=0;i<n-1;i++){
		
		char **s = crea_array_str(n,myVectorS[messi-1]);
			
		s = ruota_str(n,s);
		
		myVectorS[messi] = s;
		messi++;
		
		//stampa_array(myVectorS[messi-1],n);
		if(find==true)
			break;
	}
	
	myVectorS = realloc(myVectorS,sizeof(char **)*messi);
	
	if(myVectorS == NULL)
		termina("Errore realloc");
	
	*righe = messi;
	return myVectorS;
}

char **ruota_str(int n,char *s[]){
	
	char *tmp = s[0];
	
	for(int i = 0;i<(n-1);i++)
		s[i] = s[i+1];
		
	s[n-1] = tmp;
	
	return s;
}

char **crea_array_str(int dim,char *a[]){

	char **s = malloc(sizeof(char *)*dim);
	
	if(s==NULL)
		termina("Errore malloc");
		
	for(int i = 0;i<dim;i++)
		s[i] = strdup(a[i]);
	
	return s;
}

void stampa_array(char *s[],int dim){
	
	for(int i=0;i<dim;i++)
		fprintf(stdout,"%s\t",s[i]);
	fprintf(stdout,"\n");
}

void dealloca_array(char *s[],int dim){
	
	for(int i=0;i<dim;i++)
		free(s[i]);
	free(s);
}

int *crea_array_int(int dim,int *b){
	
	//E' CORRETTO???
	int *a = malloc(sizeof(int)*dim);
	
	if(a==NULL)
		termina("Errore malloc");	
	
	for(int i=0;i<dim;i++)
		a[i] = b[i];
		
	return a;
}

int **rotazioni_int(int a[], int n, int *righe){
	
	int **myVector = malloc(sizeof(int *)*n);
	
	if(myVector == NULL) 
		termina("Errore malloc 1");	
	
	int messi = 0;
	myVector[messi] = a;	
	messi++;
	
	stampa_array_int(a,n);
	
	bool find;
	if(n%2==0){
		find = true;
		for(int i=0;i<n-2;i++){
			if(a[i] != a[i+2])
				find = false;
		}
	}
	else
		find = false;
	
	for(int j = 0;j<n-1;j++){
		
		int *b = crea_array_int(n,myVector[messi-1]);	
		
		b = ruota_int(b,n);
		
		myVector[messi] = b;
		messi++;
		
		if(find)
			break;
}
	if(n!=messi){
		myVector = realloc(myVector,sizeof(int *)*messi);
	
		if(myVector==NULL)
			termina("Errore realloc");
	}
	
	*righe = messi;
	return myVector;
}

void stampa_array_int(int *a,int dim){
	for(int i = 0;i<dim;i++)
		fprintf(stdout,"%d\t",a[i]);
	fprintf(stdout,"\n");
}

int *ruota_int(int a[], int n){
	
	int el = a[0];
	
	for(int i = 0;i<n-1;i++)
		a[i] = a[i+1];
		
	a[n-1] = el;
	
	return a;
}

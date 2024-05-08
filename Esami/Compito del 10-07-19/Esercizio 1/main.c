#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]);

/*
1a) Si scriva una funzione

int *leggi_array(char *nomefile, int *num)
che dato il nome di un file nomefile alloca e restituisce un array di interi ottenuto 
leggendo gli interi da nomefile in formato binario (4 byte per ogni intero). 
La funzione deve restituire il puntatore al primo elemento dell'array e memorizzare in 
num il numero di elementi dell'array (che sarà uguale alla lunghezza del file diviso 4). 
Se il file non esiste o non può essere letto la funzione deve restituire NULL e porre num a 
zero
*/

int *leggi_array(char *nomefile, int *num);

/*
1b) Si utilizzi la struct

 typedef struct cop {
   int primo;
   int secondo;
   struct cop *next; 
 } coppia;

che permette di rappresentare un elemento di una lista di coppie di interi.

Si scriva una funzione:

coppia *unisci(int *a1, int n1, int *a2, int n2)

che dati i due array a1 e a2 con rispettivamente n1 e n2 elementi restituisce la lista di 
coppie i cui elementi sono ottenuti prendendo primo da a1 e secondo da a2 rispettando 
l'ordine. 

Ad esempio, se a1 = {1,4,0,5} e a2 = {3, -1, 1, 4, 4, 8} la lista restituita deve contenere 
le coppie

(1,3) (4,-1) (0,1) (5,4)

in quest'ordine. 
Si noti che, come nell'esempio precedente, il numero di elementi della lista deve essere 
pari al numero di elementi dell'array più corto; gli elementi finali dell'array più lungo 
sono semplicemente ignorati.

*/

typedef struct cop {
   int primo;
   int secondo;
   struct cop *next; 
 } coppia;

coppia *unisci(int *a1, int n1, int *a2, int n2);

coppia *crea_coppia(int primo,int secondo);

void stampa_coppie(coppia *lis,FILE *pFile);

/*
1c) Si scriva una funzione

void scrivilistafun(FILE *f, coppia *lis, int (*fun)(int))

che dato una lista di coppie lis, scrive in formato testo nel file f i valori ottenuti 
applicando la funzione fun ad ognuno degli interi di ogni coppia. 
Ad esempio, se lis contiene le 4 coppie riportate sopra e la funzione fun restituisce il
quadrato del suo input, nel file f devono essere scritte le 4 righe.

1 9
16 1
0 1
25 16
*/

void scrivilistafun(FILE *f, coppia *lis, int (*fun)(int));
int elevamento_al_quadrato(int n);

/*
1d) Si scriva un main che legge dalla linea di comando i nomi di due file 
binari, e crea due array di interi chiamando la funzione leggi_array passando i nomi 
dei due file letti sulla riga di comando. 
Successivamente il main deve creare una lista di coppie chiamando la funzione unisci 
passando come argomenti i due array precedentemente ottenuti. La lista di coppie deve 
essere infine passata alla funzione scrivilistafun con stderr come primo argomento e la 
funzione che restituisce il quadrato del suo input come terzo argomento. Prima di terminare 
il programma deve deallocare tutta la memoria utilizzata; utilizzare valgrind per la 
verifica.
*/
void dealloca_lista(coppia *lis);

int main(int argc,char *argv[]){
	
	if(argc!=3)
		termina("Uso: nome_file nome_file");
	
	//definisco i due file in binario con i valori del for
	FILE *pFile1 = fopen(argv[1],"wb");
	
	if(pFile1 == NULL)
		termina("Errore fopen");
	
	for(int i = 1;i<8;i++)
		fwrite(&i,sizeof(int),1,pFile1);
	
	fclose(pFile1);
	
	FILE *pFile2 = fopen(argv[2],"wb");
	
	if(pFile2 == NULL)
		termina("Errore fopen");
		
	for(int i = -15;i<3;i++)
		fwrite(&i,sizeof(int),1,pFile2);
	
	fclose(pFile2);
	
	int dimA;
	int *a = leggi_array(argv[1],&dimA);
	
	int dimB;
	int *b = leggi_array(argv[2],&dimB);
	
	coppia *lis = unisci(a,dimA,b,dimB);
	
	stampa_coppie(lis,stdout);
	
	fprintf(stdout,"\n");
	scrivilistafun(stdout,lis,elevamento_al_quadrato);
	
	free(a);
	free(b);
	dealloca_lista(lis);
	
	return 0;
}

void dealloca_lista(coppia *lis){
	
	if(lis==NULL)
		return;
	
	dealloca_lista(lis->next);
	free(lis);
}

void scrivilistafun(FILE *pFile,coppia *lis,int (*fun)(int)){
	
	if(lis==NULL)
		return;
		
	lis->primo = fun(lis->primo);
	lis->secondo = fun(lis->secondo);
	
	fprintf(pFile,"%d %d\n",lis->primo,lis->secondo);
	
	scrivilistafun(pFile,lis->next,fun);
	
	return;
}

int elevamento_al_quadrato(int n){
	return n*n;
}

void stampa_coppie(coppia *lis,FILE *pFile){
	
	if(lis==NULL)
		return;
	
	fprintf(pFile,"%d %d\n",lis->primo,lis->secondo);
	
	stampa_coppie(lis->next,pFile);
	
	return;
}

coppia *unisci(int *a1, int n1, int *a2, int n2){
	
	int i;
	if(n1>n2)
		i = n2-1;
	else 			//(n1<n2) oppure n1==n2
		i = n1 - 1;
	
	coppia *lis = NULL;
	while(i>=0){
		
		coppia *c = crea_coppia(a1[i],a2[i]);
		
		c->next = lis;
		lis = c;
		i--;
	}
	
	return lis;
}

coppia *crea_coppia(int primo,int secondo){

	coppia *c =  malloc(sizeof(coppia));
		
	if(c==NULL)
		termina("Errore malloc");
		
	c->primo = primo;
	c->secondo = secondo;
	c->next = NULL;
	
	return c;
}

int *leggi_array(char *nomefile, int *num){
	
	FILE *pFile = fopen(nomefile,"rt");
	
	if(pFile == NULL){
		*num = 0;
		return NULL;
	}
	
	assert(pFile != NULL);
	
	if(fseek(pFile,0,SEEK_END)<0)
		termina("Errore fseek");
	
	long lunghezza = ftell(pFile);
	
	if(lunghezza<0)
		termina("Errore ftell");
	
	int interi = lunghezza/sizeof(int);
	
	int *a = malloc(sizeof(int)*interi);
	
	if(a==NULL)
		termina("Errore malloc");
	
	rewind(pFile);
	
	if(fread(a,sizeof(int),interi,pFile) != interi)
		termina("Errore fread");
	
	*num = interi;
	fclose(pFile);
	return a;
}

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_FAILURE);

}

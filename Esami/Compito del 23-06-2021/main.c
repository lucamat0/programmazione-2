#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	
	perror(messaggio);
	exit(EXIT_SUCCESS);
}

typedef struct {
   int primo;
   int secondo;
 } coppia;

void stampa_array(coppia *a,int dim);

//dato un puntatore ad un file binario contenente un numero pari di interi a 32 bit, 
//crea e restituisce un array di coppie utilizzando gli interi del file 
//(i primi due interi formano la prima coppia, gli interi 3 e 4 la seconda coppia, e così via).
//La funzione deve restituire il puntatore al primo elemento dell'array creato e, 
//attraverso il parametro, n il numero di coppie presenti nell'array.
coppia *leggi_coppie(FILE *f, int *n);

//data una coppia restituisce la somma delle componenti. 
int somma(coppia c) {
   return (c.secondo + c.primo);
}
/*
Dato un array a[] contenente n coppie, alloca e restituisce un nuovo array di n 
coppie che contiene le stesse coppie di a[] ordinate per somma decrescente. 

Ad esempio, se l'array a[] contiene

[(3,1), (5,2), (-4,3), (2,8), (1,-1)]
l'invocazione della funzione deve restituire l'array

[(2,8), (5,2), (3,1), (1,-1), (-4,3)]
senza modificare l'array di input a[]. 
La funzione ordina_somma deve eseguire l'ordinamento utilizzando la funzione di libreria 
qsort.
*/

int ordina_coppie_somma_decrescente(const coppia *c1,const coppia *c2);

void scrivi_array_file_binario(coppia *a,int dim,FILE *pFile);

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: nome_file_coppie_bin");
	
	//apre in lettura il file di nome argv[1]
	FILE *pFile = fopen(argv[1],"rb");
	
	if(pFile==NULL)
		termina("Errore fopen");
	//crea un array di coppie invocando leggi_coppie e passando il file appena 
	//aperto di nome argv[1]
	int dim;
	coppia *a = leggi_coppie(pFile,&dim);
	fclose(pFile);
	
	puts("--- Coppie non ordinate ---");
	stampa_array(a,dim);
	puts("--- ---");
	
	//scrive in un file prima.bin l'array di coppie non ordinato, 
	//in formato binario, 4 byte per intero quindi 8 byte per ogni coppia
	FILE *pFile2 = fopen("prima.bin","wb");
	
	if(pFile2==NULL)
		termina("Errore fopen");
	
	scrivi_array_file_binario(a,dim,pFile2);
	fclose(pFile2);
	
	coppia *b = malloc(sizeof(coppia)*dim);
	
	if(b==NULL)
		termina("Errore malloc");
	
	for(int i=0;i<dim;i++)
		b[i] = a[i]; 
	
	//invoca la funzione ordina_somma per creare l'array di coppie ordinato rispetto 
	//alla somma
	qsort(b,dim,sizeof(coppia),(__compar_fn_t)ordina_coppie_somma_decrescente);
	
	puts("--- Coppie ordinate ---");
	stampa_array(b,dim);
	puts("--- ---");
	
	//scrive in un file dopo.bin l'array di coppie ordinato, in formato binario, 
	//4 byte per intero quindi 8 byte per ogni coppia
	FILE *pFile3 = fopen("dopo.bin","wb");
	
	if(pFile3==NULL)
		termina("Errore fopen");
	
	scrivi_array_file_binario(b,dim,pFile3);
	fclose(pFile3);
	
	//dealloca tutta la memoria utilizzata (verificare con valgrind) e termina
	free(a);
	free(b);
	
	return 0;
}

void scrivi_array_file_binario(coppia *a,int dim,FILE *pFile){

	int *b = malloc(sizeof(int)*2);
	
	if(b==NULL)
		termina("Errore malloc");
	
	
	for(int i=0;i<dim;i++){
		
		b[0] = a[i].primo;
		b[1] = a[i].secondo;
		
		fwrite(b,sizeof(int),2,pFile);
	}
	
	free(b);
}

coppia *leggi_coppie(FILE *f, int *n){
	
	assert(f!=NULL);
	
	int e = fseek(f,0,SEEK_END);
	
	if(e<0)
		termina("Errore fseek");
	
	long lunghezza = ftell(f);
	
	int interi = lunghezza/sizeof(int);
	
	assert(interi>0);
	
	int *a = malloc(sizeof(int)*interi);
	
	if(a==NULL)
		termina("Errore malloc");
	
	rewind(f);
	
	if(fread(a,sizeof(int),interi,f)!=interi)
		termina("Errore fread");

	if(interi%2!=0)
		interi = interi-1;
		
	coppia *b = malloc(sizeof(coppia *)*(interi/2));
	
	if(b==NULL)
		termina("Errore malloc");
	
	int j = 0;
	for(int i=0;i<interi;i+=2){
		b[j].primo = a[i];
		b[j].secondo = a[i+1];
		j++;
	}
	
	free(a);
	*n = interi/2;
	return b;
}

int ordina_coppie_somma_decrescente(const coppia *c1,const coppia *c2){
	
	if(somma(*c1)>somma(*c2))
		return -1;
	else if(somma(*c1)<somma(*c2))
		return 1;
	else 
		return 0;
}

void stampa_array(coppia *a,int dim){
	
	for(int i=0;i<dim;i++)
		fprintf(stdout,"%d %d\t",a[i].primo,a[i].secondo);
	fprintf(stdout,"\n");
}


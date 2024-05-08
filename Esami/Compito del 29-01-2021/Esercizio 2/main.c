/*
2a) Scrivere una funzione

int coppie_uni(int n)

che dato un intero positivo n restituisce quante sono le coppie di uni consecutivi che appaiono 
all'interno della rappresentazione binaria di n. Ad esempio (tra parentesi la rappresentazione 
binaria dell'input):

coppie_uni(8) -> 0 (1000) coppie_uni(17) -> 0 (10001) coppie_uni(11) -> 1 (1011) 
coppie_uni(27) -> 2 (11011) coppie_uni(14) -> 2 (1110) coppie_uni(15) -> 3 (1111)

Commento al testo
2b) Scrivere un programma che legge dalla riga di comando il nome di un file nomefile e un intero 
positivo n e crea un file nomefile contenente l'elenco di tutti gli interi positivi minori o uguali 
a n la cui rappresentazione binaria contiene esattamente una coppia di uni consecutivi. Ad esempio scrivendo

esercizio2 pippo 30

deve essere creato il file binario pippo contenente gli interi (di fianco ad ogni intero indico tra 
parentesi la rapprentazione binaria, voi non dovete scriverla):

3 (11)
6 (110)
11 (1011)
12 (1100)
13 (1101)
19 (10011)
22 (10110)
24 (11000)
25 (11001)
26 (11010)
Il file creato deve essere in formato binario quindi usare 4 byte per ogni intero; 
nell'esempio precedente il file pippo deve avere lunghezza 36 byte. 
Potete usare il comando od -An -t d4 per visualizzare sul terminale gli interi contenuti nel file.
*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

int coppie_uni(int n);

int main(int argc,char *argv[]){
	
	if(argc!=3)
		termina("Uso: file_dove_salvare_interi numero_intero");

/*	
	int n = coppie_uni(atoi(argv[1]));
	
	fprintf(stdout,"%d contiene %d di uni consecutivi\n",atoi(argv[1]),n);
	//fprintf(stdout,"sizeof(int): %ld\n",sizeof(int));
*/
	int n = atoi(argv[2]);
	FILE *pFile = fopen(argv[1],"wb");
	
	if(pFile==NULL)
		termina("Errore fopen");
	
	for(int i=1;i<=n;i++){
		if(coppie_uni(i)==2)
			fwrite(&i,sizeof(int),1,pFile);
	}
	
	fclose(pFile);
	
	
	return 0;
}

int coppie_uni(int n){
	
	int num_uni_consecutivi = 0;
	
	int conta = 0;
	for(int i=0;i<32;i++){
	//for(int i=0;i<=sizeof(int)*8;i++){
		if((n &(1<<i))!=0){
			conta++;
			if(conta>=2 && conta>num_uni_consecutivi){
				num_uni_consecutivi = conta;
			}
		}
		else
			conta = 0;
	}
	return num_uni_consecutivi;
}

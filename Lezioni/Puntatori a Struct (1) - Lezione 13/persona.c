#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp

//spesso con le struct si utilizzano i puntatori
//essendo molto grandi e' piu' efficente.
typedef struct{
	char *nome;			//8 byte
	char *cognome;		//8 byte
	int eta;			//4 byte
}persona;						//totale 20 byte

void termina(const char messaggio []);

persona *leggi_punt_persona_da_file(FILE *pFile);
persona leggi_persona_da_file(FILE *pFile);

void scrivi_persona(FILE *pFile,const persona *p);
void distruggi_persona(persona *p);

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: nome_del_file");
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	persona p = leggi_persona_da_file(pFile);
	persona *q = leggi_punt_persona_da_file(pFile);
	
	scrivi_persona(stdout,&p);
	
	free(p.nome);
	free(p.cognome);
	
	scrivi_persona(stdout,q);
	
	distruggi_persona(q);
	
	fclose(pFile);
	return 0;
}

void distruggi_persona(persona *p){

	free(p->nome);
	free(p->cognome);
	free(p);
}

persona leggi_persona_da_file(FILE *pFile){
		
	persona p;
	
	char nome[100];
	char cognome[100];
	int eta;
	
	fscanf(pFile,"%99s %99s %d",nome,cognome,&eta);
	
	p.nome = strdup(nome);
	p.cognome = strdup(cognome);
	p.eta = eta;
	
	return p;
}
//restituisce un puntatore dopo aver letto la persona dal file
persona *leggi_punt_persona_da_file(FILE *pFile){
		
	//Ho creato un oggetto persona, il puntatore p punta una zona di memoria 
	//che posso utilizzare anche fuori dalla funzione perche' abbiamo utilizzato
	//la malloc
	persona *p = malloc(sizeof(persona));
	
	if(p==NULL)
		termina("Errore malloc");
	
	char nome[100];
	char cognome[100];
	int eta;
	
	fscanf(pFile,"%99s %99s %d",nome,cognome,&eta);
	
	p->nome = strdup(nome);
	p->cognome = strdup(cognome);
	p->eta = eta;
	
	return p;
}

//Usiamo il puntatore per alleggerire il passaggio di dati da una funzione all'altra
//Per evitare che mi venga modificata la persona, che la passo per riferimento,
//per rendere piu' agile il programma, inserisco il suffisso const.
void scrivi_persona(FILE *pFile,const persona *p){

	//Scrittura corretta ma poco utilizzata:
	//fprintf(pFile,"Nome: %s, Cognome: %s, Eta': %d;\n",(*p).nome,(*p).cognome,(*p).eta);
	
	//Scrittura corretta ma piu' utilizzata:
	fprintf(pFile,"Nome: %s, Cognome: %s, Eta': %d;\n",p->nome,p->cognome,p->eta);
}

void termina(const char messaggio[]){
	perror(messaggio);
	exit(EXIT_FAILURE); 
}

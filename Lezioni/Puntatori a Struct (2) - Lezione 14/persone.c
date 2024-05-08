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

int pos_piu_vecchia(persona **p,int n);

int main(int argc,char *argv[]){
	
	if(argc!=2)
		termina("Uso: nome_del_file");
	
	FILE *pFile = fopen(argv[1],"rt");
	
	if(pFile == NULL)
		termina("Errore fopen");
	
	//sono il numero di elementi che voglio memorizzare all'interno dell'array = numero di persone.
	int size = 2;
	//numero di elementi che si trovano nel array persone, inizialmente a 0.
	int messi = 0;
	
	//ci vogliono due asterischi perche' e' un puntatore a un area di memoria che contiene un puntatore,
	//il seguente puntatore punta a sua volta a un altra area di memoria che punta a una persona.
	persona **persone = malloc(size*sizeof(persona*));		//3*8 byte = 24 byte
	
	if(persone==NULL)
		termina("Errore malloc");
	
	persona *p;
	
	//continua a ciclare fin quando la funzione non ritorna il valore NULL
	while((p = leggi_punt_persona_da_file(pFile)) != NULL){
		
		if(messi==size){
			size *= 2;
			persone = realloc(persone,size*sizeof(persona*));
		
			if(persone==NULL)
				termina("Errore realloc");
		}
			persone[messi] = p;
			messi++;
	}
	
	//vado a svolgere la realloc se messi NON E' UGUALE a size
	if(messi != size){
		
		persone = realloc(persone,messi*sizeof(persona*));
		
		if(persone == NULL)
			termina("Errore realloc");
	}
	
	fclose(pFile);
	
	fprintf(stdout,"--- Lista persone ---\n");
	for(int i = 0;i<messi;i++)
		scrivi_persona(stdout,persone[i]);
	fprintf(stdout,"--- Fine lista persone ---\n");
	
	puts(persone[0]->nome);		//accedo al campo nome della prima persona
	
	persone[0]->nome[0] = 'Z'; 		//vado a modificare l'iniziale della prima persona.
	
	puts(persone[0]->nome);	
	
	//ordinamento per eta 
	//->trovo il piu' vecchio e lo metto in fondo all'array iterando l'array persone da 0 a messi -1
	int dim_messi = messi;	
	for(int ultimo = messi-1;ultimo>=1;ultimo--){
		//metto in a[ultimo] il piu' vecchio
		//Scambio il piu' vecchio mettendolo in fondo e l'elemento in fondo prende il posto del elemento che va in fondo
		
		int pos_ultimo = pos_piu_vecchia(persone,dim_messi);
		
		persona *tmp = persone[dim_messi-1];
		
		persone[dim_messi-1] = persone[pos_ultimo]; 
		persone[pos_ultimo] = tmp;
		dim_messi--;
	}
	
	fprintf(stdout,"--- Lista ordinata per eta' ---\n");
	for(int i = 0;i<messi;i++)
		scrivi_persona(stdout,persone[i]);
	fprintf(stdout,"--- Fine lista ordinata per eta' ---\n");
	
	for(int i = 0;i<messi;i++)
		distruggi_persona(persone[i]);
	
	free(persone);
	
	return 0;
}

//devo ritornare la posizione di dove si trova la posizione con l'eta piu' alta.
int pos_piu_vecchia(persona **p,int n){
	
	assert(p!=NULL);
	assert(n>0);
	
	//eta massima tra tutte le persone
	int max_eta = p[0]->eta;
	//posizione in cui si trova la massima eta
	int posizione_max = 0;
	
	for(int i = 1;i<n;i++){
		if(p[i]->eta>max_eta){
			max_eta = p[i]->eta;
			posizione_max = i;
		}
	}
	
	return posizione_max;
}

void distruggi_persona(persona *p){

	free(p->nome);
	free(p->cognome);
	free(p);
}

//restituisce un puntatore dopo aver letto la persona dal file
//restituisce a null se non riesce a leggere i dati di una persona
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
	
	int e = fscanf(pFile,"%99s %99s %d",nome,cognome,&eta);
	
	if(e != 3){
		free(p);
		return NULL;
	}
		
	
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

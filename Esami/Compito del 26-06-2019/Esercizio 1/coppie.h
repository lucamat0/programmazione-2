typedef struct cop {
   int primo;
   int secondo;
   struct cop *next; 
 } coppia;
 
// crea una coppia contenente i valori x e y
coppia *crea_coppia(int x, int y);

// inserisce l'elemento el in cima alla lista lis
coppia *inserisci_coppia(coppia *lis, coppia *el);

// legge 2 interi dal file binario f (8 byte in totale) e crea una coppia 
// con i valori corrispondenti chiamando la funzione crea_coppia() 
// restituisce NULL se non e' possibile leggere i due interi dal file f
coppia *crea_coppia_bin(FILE *f);
// crea una lista con tutti gli interi presenti nel file
// il cui nome e' nomefile. Si supponga che gli interi
// siano memorizzati nel file in formato binario e che quindi
// devono essere letti con crea_coppie_bin().
// L'ordine con cui le coppie appaiono nel file non e' importante
// se non e' possibile leggere dal file la funzione deve
// restituire la lista vuota
coppia *crea_lista(char *nomefile);

// stampa sul file f gli interi della coppia el separati da uno spazio
void stampa_coppia(FILE *f, coppia *el);

// stampa sul file f tutte le coppie di lis separate da \n
// questa funzione *deve* utilizzare stampa_coppia() 
void stampa_lista_coppie(FILE *f, coppia *lis);

// restituisce un puntatore alla coppia della lista lis 
// la cui somma delle componenti (primo+secondo) ha valore massimo
// se ci sono più coppie con la stessa somma delle componenti
// restituire quella più lontana dalla testa della lista.  
coppia *cerca_coppia_maxsomma(coppia *lis);

// restituisce un puntatore alla prima coppia della lista lis 
// per cui la funzione f applicata ai campi primo e secondo 
// restituisce true. Se non esiste una tale coppia la funzione
// deve restituire NULL. 
coppia *cerca_coppia(coppia *lis, bool (*f)(int, int));

// dealloca tutti gli elementi della lista lis
void distruggi_lista_coppie(coppia *lis);

void termina(const char messaggio[]);

coppia *duplica_lista(coppia *lis, bool (*f)(int, int));

coppia *inserisci_coppia_coda(coppia *lis,coppia *el);




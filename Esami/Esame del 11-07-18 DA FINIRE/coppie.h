 typedef struct cop {
   int primo;
   int secondo;
   struct cop *next; 
 } coppia;
 
 // crea una coppia contenente i valori x e y
coppia *crea_coppia(int x, int y);

// inserisce l'elemento el in cima alla lista lis
coppia *inserisci_coppia(coppia *lis, coppia *el);

// stampa sul file f gli interi della coppia el separati da uno spazio
void stampa_coppia(FILE *f, coppia *el);

// stampa sul file f tutte le coppie di lis separate da \n
// questa funzione *deve* utilizzare stampa_coppia() 
void stampa_lista_coppie(FILE *f, coppia *lis);

// restituisce la prima coppia della lista lis la cui somma è s
coppia *cerca_coppia(coppia *lis, int s);

// stampa sul file f tutte le coppie di lis la cui somma e' s
// questa funzione deve utilizzare cerca_coppia() e stampa_coppia()
void cerca_e_stampa_coppie(FILE *f, coppia *lis, int s);

// restituisce il numero di coppie i cui elementi passati a f() restituiscono true
int conta_coppie(coppia *lis, bool (*f)(int, int));

// dealloca tutti gli elementi della lista lis
void distruggi_lista_coppie(coppia *lis);

void termina(const char messaggio[]);

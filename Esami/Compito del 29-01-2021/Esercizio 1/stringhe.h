
typedef struct str {
  char *s;
  struct str *next; 
} stringa;

void termina(const char messaggio[]);

// crea una un elemento di tipo stringa contenente una copia di *s
// per duplicare un array di caratteri usare strdup()
stringa *crea_stringa(char *s);

// inserisce l'elemento el in testa alla lista lis
stringa *inserisci(stringa *lis, stringa *el);

// stampa sul file f la stringa in el, 
void stampa_stringa(FILE *f, stringa *el, bool reverse);

// stampa sul file f tutte le stringhe di lis separate da \n
// questa funzione *deve* utilizzare stampa_stringa()
void stampa_lista(FILE *f, stringa *lis);

// dealloca tutti gli elementi della lista lis
// e anche tutti gli array di caratteri a cui questi elementi puntano
void distruggi_lista(stringa *lis);

//----------------------------------------------------------------------
stringa *duplica_se_pari(stringa *lis, int (*fun)(char *));

int conta_caratteri(char s[]);
int conta_maiuscole(char *s);

stringa *gestisci_lettura_file_testo(FILE *pFile);

stringa *leggi_file_testo(FILE *pFile);

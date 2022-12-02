#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studente{
    char nome[20];
    char cognome[20];
    int codicePersona;
    int voto;
} studente;

studente* inserisci_stundeti(int n);
int cerca_studente(studente *s, int n);
studente* cerca_studente_ric(studente *s, int n, char *cognome, char *nome);
studente* elenco_rimandati(studente *s, int n, int *nr);
studente* elimina_studente(studente *s, int *n, int pos);
void stampa_elenco(studente *s, int n);

int main(int argc, const char * argv[]) {
    studente *studenti = NULL;
    studente *studentiRimandati = NULL;
    
    int r;
    int n=0;
    int nr=0;
    
    do{
        printf("Menu\n");
        printf("1) Inserisci studenti (azzerando l'array)\n");
        printf("2) Cerca studente\n");
        printf("3) Crea elenco rimandati\n");
        printf("4) Elimina studente\n");
        printf("5) ESCI\n");
        printf(">> ");
        scanf("%d",&r);
        
        switch (r) {
            case 1:
                if (studenti!=NULL){
                    free(studenti);
                    studenti = NULL;
                }
                if (studentiRimandati!=NULL){
                    free(studentiRimandati);
                    studentiRimandati = NULL;
                }
                
                printf("Quanti studenti vuoi inserire? ");
                scanf("%d",&n);
                studenti = inserisci_stundeti(n);
                stampa_elenco(studenti, n);
                
                break;
            case 2:
                if (cerca_studente(studenti, n)<0)
                    printf("Studente non trovato\n");
                else
                    printf("Studente trovato\n");
                
                //oppure
                if (cerca_studente_ric(studenti, n, "Aieie", "Brazov")==NULL)
                    printf("Studente non trovato\n");
                else
                    printf("Studente trovato\n");
                break;
            case 3:
                studentiRimandati = elenco_rimandati(studenti, n, &nr);
                stampa_elenco(studentiRimandati,nr);
                break;
            case 4:
                studenti = elimina_studente(studenti, &n, cerca_studente(studenti, n));
                stampa_elenco(studenti,n);
                break;
        }
        
    }while(r!=5);

    return 0;
}

studente* inserisci_stundeti(int n){
    studente *stud = (studente*)malloc(sizeof(studente)*n);
    int i;
    for (i=0; i<n; i++){
        printf("Inserisci cognome: ");
        scanf(" %s", stud[i].cognome);
        printf("Inserisci nome: ");
        scanf(" %s", stud[i].nome);
        printf("Inserisci codice persona: ");
        scanf(" %d", &stud[i].codicePersona);
        printf("Inserisci voto: ");
        scanf(" %d", &stud[i].voto);
        printf("\n");
    }
    return stud;
}

int cerca_studente(studente *s, int n){
    char cognome[20];
    char nome[20];
    int i;
    
    if(n==0)
        return -1;
    
    printf("Inserisci cognome da cercare");
    scanf(" %s",cognome);
    printf("Inserisci nome da cercare");
    scanf(" %s", nome);
    
    /*
    studente *s_inizio = s;
    for (;s<s_inizio+n; s++){
        
    }
    */
    for (i = 0; i<n; i++){
        if ((strcmp(s[i].cognome,cognome)==0) && (strcmp(s[i].nome, nome)==0))
            return i;
    }
    return -1;
}

studente* cerca_studente_ric(studente *s, int n, char *cognome, char *nome){
    if (n==0)
        return NULL;
    if (strcmp(s->cognome,cognome)==0 && strcmp(s->nome,nome)==0)
        return s;
    else
        return cerca_studente_ric(s+1, n-1, cognome, nome);
}

studente* elenco_rimandati(studente *s, int n, int *nr){
    studente *studRimandati = NULL;
    int i;
    int nuova_lun = 0;

    if (n==0)
        return NULL;
    
    for (i = 0; i<n; i++){
        if (s[i].voto<18)
            nuova_lun++;
    }
    
    //So quanto deve essere lungo il secondo array
    studRimandati = (studente*)malloc(sizeof(studente)*(nuova_lun));
    
    nuova_lun = 0;
    for (i = 0; i<n; i++){
        if (s[i].voto<18){
            studRimandati[nuova_lun] = s[i];
            nuova_lun++;
        }
    }
    
    *nr = nuova_lun;
    return studRimandati;
}

studente* elimina_studente(studente *s, int *n, int pos){
    if ((*n == 0) || (*n<pos) || (pos == -1))
        return s;
    /*
    for (int i= pos; i<(*n)-1; i++){
        s[i] = s[i+1];
    }
    for(studente *i=s+pos;i<s+(*n)-1; i++)
        *i=*(i+1);
   */
    memcpy(s+pos, s+pos+1, sizeof(studente)*((*n)-pos-1));
    (*n)--;
    if (*n==0){
        free(s);
        return NULL;
    }
    else{
        s = realloc(s,sizeof(studente)*(*n));
        return s;
    }
        
}

void stampa_elenco(studente *s, int n){
    int i;
    for (i=0; i<n; i++){
        printf("Cognome: %s\nNome: %s\nCodice persona: %d\nVoto: %d\n\n",s[i].cognome,s[i].nome,s[i].codicePersona,s[i].voto);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** inserisci(int *n);
void stampa(char **stringa, int i);
void stampaParola(char *parola);
void stampaParolaRic(char *parola);

int main(int argc, const char * argv[]) {
    char **parole;
    int num = 0;
    
    parole = inserisci( &num);
    stampa(parole, num);
    
    return 0;
}

void stampaParola(char *parola){
    char *i;
    int len = 0;
    for (i=parola; *i!='\0'; i++)
        len++;
    for (i=parola+len-1; i>=parola; i--)
        printf("%c",*i);
    printf("\n");
}

void stampaParolaRic(char *parola){
    if (*parola == '\0')
        return;
    stampaParolaRic(parola+1);
    printf("%c",*parola);
}

void stampa(char **parole, int i){
    for (i=i-1; i>=0; i--){
        stampaParola(parole[i]);
    }
}

char** inserisci(int *n){
    char **stringa;
    char str[400]; //temperanea
    int len = 0;
    
    printf("Quante stringhe vuoi inserire? ");
    scanf("%d",n);
    
    stringa = (char**)malloc(sizeof(char*)*(*n));
    
    do{
        printf("Inserisci la stringa: ");
        scanf(" %s",str);
        stringa[len] = (char*)malloc(sizeof(char)*strlen(str)+1);
        strcpy(stringa[len],str);
        len++;
    }while(len<*n);
    return stringa;
}



#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    struct node *next;
} node;

typedef node *ptrNode;

ptrNode inserisci_in_testa(ptrNode lista, int l);
void inserisci_in_coda(ptrNode *lista, int l);
ptrNode inserisci_in_coda_ric(ptrNode lista, int l);

void stampa_lista(ptrNode lista);
void stampa_lista_ric(ptrNode lista);

int main(int argc, const char * argv[]) {
    ptrNode lista = NULL;
    
    inserisci_in_coda(&lista, 4);
    lista = inserisci_in_testa(lista, 1);
    lista = inserisci_in_testa(lista, 2);
    lista = inserisci_in_testa(lista, 3);
    inserisci_in_coda(&lista, 5);
    lista = inserisci_in_coda_ric(lista, 6);
    stampa_lista_ric(lista);
    return 0;
}

ptrNode inserisci_in_testa(ptrNode lista, int l){
    ptrNode temp = (ptrNode)malloc(sizeof(node));
    temp->num = l;
    temp->next = lista;
    return temp;
}

void inserisci_in_coda(ptrNode *lista, int l){
    ptrNode currentTail = *lista;
    ptrNode temp;
    
    temp = (ptrNode)malloc(sizeof(node));
    temp->next = NULL;
    temp->num = l;
    
    if (*lista==NULL){
        *lista = temp;
        return;
    }
    
    while(currentTail->next != NULL)
        currentTail = currentTail->next;
    
    currentTail->next = temp;

}

ptrNode inserisci_in_coda_ric(ptrNode lista, int l){
    ptrNode temp;
    
    if (lista == NULL){
        temp = (ptrNode)malloc(sizeof(node));
        temp->num = l;
        temp->next = NULL;
        return temp;
    }
    else{
        lista->next = inserisci_in_coda_ric(lista->next, l);
        return lista;
    }
}

void stampa_lista(ptrNode lista){
    for (;lista!=NULL; lista=lista->next){
        printf("%d\n",lista->num);
    }
}
void stampa_lista_ric(ptrNode lista){
    if (lista==NULL)
        return;
    printf("%d\n",lista->num);
    stampa_lista_ric(lista->next);
}

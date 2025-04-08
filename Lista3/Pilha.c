#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento Elem;

Pilha* cria_Pilha() {
    Pilha* pi = (Pilha*) malloc(sizeof(Elem*));
    if (pi != NULL)
        *pi = NULL;
    return pi;
}

int push2(Pilha *p, struct aluno *vet, int qtd) {
    if (p == NULL) return 0;

    for (int i = 0; i < qtd; i++) {
        Elem* no = (Elem*) malloc(sizeof(Elem));
        if (no == NULL) return 0;

        no->dados = vet[i];
        no->prox = *p;
        *p = no;
    }
    return 1;
}

int pop2(Pilha *p, struct aluno *vet, int qtd) {
    if (p == NULL || *p == NULL) return 0;
    for (int i = 0; i < qtd; i++) {
        if (*p == NULL) break;  
        Elem *no = *p;
        vet[i] = no->dados;
        *p = no->prox;
        free(no);
        printf("Desempilhado: %d %s %.2f %.2f %.2f\n", vet[i].matricula, vet[i].nome, vet[i].n1, vet[i].n2, vet[i].n3);
    }
    return 1;
}

#ifndef PILHA_H
#define PILHA_H

struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct elemento {
    struct aluno dados;
    struct elemento* prox;
} Elem;

typedef Elem* Pilha;

Pilha* cria_Pilha();
int push2(Pilha* p, struct aluno* vet, int qtd);  
int pop2(Pilha* p, struct aluno* vet, int qtd);   

#endif


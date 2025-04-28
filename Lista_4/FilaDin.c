#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"

Fila* cria_Fila() {
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if (fi != NULL) {
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi) {
    if (fi != NULL) {
        Elem* no;
        while (fi->inicio != NULL) {
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int consulta_Fila(Fila* fi, struct aluno *al) {
    if (fi == NULL)
        return 0;
    if (fi->inicio == NULL)
        return 0;
    *al = fi->inicio->dados;
    return 1;
}

void imprime_Fila(Fila* fi) {
    if (fi == NULL)
        return;
    Elem* no = fi->inicio;
    while (no != NULL) {
        printf("Matricula: %d\n", no->dados.matricula);
        printf("Nome: %s\n", no->dados.nome);
        printf("Notas: %f %f %f\n", no->dados.n1, no->dados.n2, no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

int insere_Fila(Fila* fi, struct aluno al) {
    if (fi == NULL)
        return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if (fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi) {
    if (fi == NULL)
        return 0;
    if (fi->inicio == NULL)
        return 0;
    Elem* no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if (fi->inicio == NULL)
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanho_Fila(Fila* fi) {
    if (fi == NULL)
        return 0;
    return fi->qtd;
}

int Fila_vazia(Fila* fi) {
    if (fi == NULL)
        return 1;
    if (fi->inicio == NULL)
        return 1;
    return 0;
}
// EX 1 ------------------------------------------------
int separa(Fila* f1, Fila* f2, int matricula_n) {
    if (f1 == NULL || f2 == NULL || f1->inicio == NULL)
        return 0;
    Elem* atual = f1->inicio;
    Elem* anterior = NULL;
    while (atual != NULL && atual->dados.matricula != matricula_n) {
        anterior = atual;
        atual = atual->prox;}
    if (atual == NULL)
        return 0;
    f2->inicio = atual->prox;
    f2->final = f1->final;
    if (anterior != NULL) anterior->prox = NULL;
    f1->final = anterior;
    f1->qtd = 0;
    f2->qtd = 0;
    Elem* temp = f1->inicio;
    while (temp != NULL) {
        f1->qtd++;
        temp = temp->prox;}
    temp = f2->inicio;
    while (temp != NULL) {
        f2->qtd++;
        temp = temp->prox;}
    return 1;
}
// EX 3 ---------------------------------------------------------------------------
void inicializarPilha(Pilha* p) {
    p->topo = NULL;
}

int pilhaVazia(Pilha* p) {
    return (p->topo == NULL);
}

int empilhar(Pilha* p, int valor) {
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->num = valor;
    no->prox = p->topo;
    p->topo = no;
    return 1;
}

int desempilhar(Pilha* p) {
    if (pilhaVazia(p))
        return 0;
    Elem* no = p->topo;
    p->topo = no->prox;
    free(no);
    return 1;
}

void inverterFila(Fila *f) {
    Pilha p;
    inicializarPilha(&p);
    while (!Fila_vazia(f)) {
        struct aluno al;
        consulta_Fila(f, &al);
        remove_Fila(f);
        empilhar(&p, al.matricula);}
    while (!pilhaVazia(&p)) {
        int valor = p.topo->num;
        desempilhar(&p);
        struct aluno al;
        al.matricula = valor;
        insere_Fila(f, al);}
}
int emfilera(Fila* fi, int valor) {
    if (fi == NULL)
        return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->num = valor;
    no->prox = NULL;
    if (fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}



// EX 4 -------------------------------------------------- ----------------------------
int filaVaziaa(Fila* f) {
    return f->qtd == 0;
}

int filaCheia(Fila* f) {
    return f->qtd == TAMANHO;
}

void FuraFila(Fila* f, struct aluno al) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível adicionar o item.\n");
        return;
    }
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return ;

    no->dados = al;
    no->prox = f->inicio;
    if (f->final == NULL)
        f->inicio = no;
    else
        f->final->prox = no;
    f->final = no;
    f->qtd++;
}

void percorrerFila(Fila* f) {
    if (filaVaziaa(f)) {
        printf("Fila vazia!\n");
        return;}
    Elem* no = f->inicio;
    while (no != NULL) {
        printf("Matrícula: %d\n", no->dados.matricula);
        printf("Nome: %s\n", no->dados.nome);
        printf("Notas: %.2f %.2f %.2f\n", no->dados.n1, no->dados.n2, no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;}
    printf("\n");
}



//EX 2 ---------------------------------------------------------------------------
// (A)
int filadefilas(Fila* f1, Fila* f2) {
    if (f1 == NULL || f2 == NULL)
        return 0;
    FDF* fd = (FDF*) malloc(sizeof(FDF));
    if (fd == NULL)
        return 0;
    fd->f1 = f1;
    fd->f2 = f2;
    fd->inicio = NULL;
    fd->final = NULL;
    fd->qtd = 0;
    return 1;
}
// (B)
int filadepilhas(Fila* f3, Pilha* p1, Pilha* p2) {
    if (f3 == NULL || p1 == NULL || p2 == NULL)
        return 0;
    FDP* fdfp = (FDP*) malloc(sizeof(FDP));
    if (fdfp == NULL)
        return 0;
    fdfp->f3 = f3;
    fdfp->p1 = p1;
    fdfp->p2 = p2;
    fdfp->inicio = NULL;
    fdfp->final = NULL;
    fdfp->qtd = 0;
    return 1;
}
// (C)
int pilhasdefilas(Fila* f1, Fila* f2) {
    if (f1 == NULL || f2 == NULL)
        return 0;
    PDF* pdf = (PDF*) malloc(sizeof(PDF));
    if (pdf == NULL)
        return 0;
    pdf->f1 = f1;
    pdf->f2 = f2;
    pdf->inicio = NULL;
    pdf->final = NULL;
    pdf->qtd = 0;
    return 1;
}
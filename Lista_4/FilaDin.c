#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    //while (no != NULL) {
        printf("Matrícula: %d\n", no->dados.matricula);
        printf("Nome: %s\n", no->dados.nome);
        printf("Notas: %.2f %.2f %.2f\n", no->dados.n1, no->dados.n2, no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    //}
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




// EX 5 -------------------------------------------------- ---------------------------- 
Aviao *inicio = NULL;
Aviao *fim = NULL;
// criar o aviao
Aviao* criarAviao() {
    Aviao *novo = (Aviao*) malloc(sizeof(Aviao));
    if (!novo) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    printf("Digite o ID do avião: ");
    scanf("%d", &novo->id);
    getchar(); // limpa o buffer
    printf("Digite o modelo do avião: ");
    fgets(novo->modelo, 50, stdin);
    novo->modelo[strcspn(novo->modelo, "\n")] = '\0'; // remove '\n'

    printf("Digite a companhia aérea: ");
    fgets(novo->companhia, 50, stdin);
    novo->companhia[strcspn(novo->companhia, "\n")] = '\0';

    novo->prox = NULL;
    return novo;}

// adicionar avião na fila
void adicionarAviao() {
    Aviao *novo = criarAviao();
    if (fim == NULL) {
        inicio = fim = novo;
    } else {
        fim->prox = novo;
        fim = novo;
    }
    printf("Avião adicionado à fila de decolagem.\n");}

// listar número de aviões na fila
void listarNumeroAvioes() {
    int contador = 0;
    Aviao *atual = inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    printf("Número de aviões na fila de decolagem: %d\n", contador);}

// autorizar decolagem do primeiro avião
void autorizarDecolagem() {
    if (inicio == NULL) {
        printf("Nenhum avião na fila para decolar.\n");
        return;
    }
    Aviao *remover = inicio;
    printf("Avião autorizado para decolagem: ID %d, Modelo %s, Companhia %s\n",
           remover->id, remover->modelo, remover->companhia);
    inicio = inicio->prox;
    if (inicio == NULL) fim = NULL;
    free(remover);}

// listar todos os aviões na fila
void listarTodosAvioes() {
    if (inicio == NULL) {
        printf("Nenhum avião na fila.\n");
        return;
    }
    Aviao *atual = inicio;
    int i = 1;
    printf("Aviões na fila de decolagem:\n");
    while (atual != NULL) {
        printf("%d. ID: %d, Modelo: %s, Companhia: %s\n", i, atual->id, atual->modelo, atual->companhia);
        atual = atual->prox;
        i++;}}

// mostrar características do primeiro avião
void listarPrimeiroAviao() {
    if (inicio == NULL) {
        printf("Nenhum avião na fila.\n");
        return;}
    printf("Primeiro avião na fila: ID: %d, Modelo: %s, Companhia: %s\n",
           inicio->id, inicio->modelo, inicio->companhia);}

// Menu principal
void menu() {
    int opcao;
    do {
        printf("\n--- Controle da Pista de Decolagem ---\n");
        printf("1. Listar número de aviões na fila\n");
        printf("2. Autorizar decolagem do primeiro avião\n");
        printf("3. Adicionar um avião à fila\n");
        printf("4. Listar todos os aviões na fila\n");
        printf("5. Listar características do primeiro avião\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 
        switch (opcao) {
            case 1: listarNumeroAvioes(); break;
            case 2: autorizarDecolagem(); break;
            case 3: adicionarAviao(); break;
            case 4: listarTodosAvioes(); break;
            case 5: listarPrimeiroAviao(); break;
            case 6: printf("Encerrando o programa.\n"); break;
            default: printf("Opção inválida.\n");}} while (opcao != 6);}


int frente(Fila *f) {
    if (f->inicio == NULL) return -1;
    return f->inicio->num;
}
            

void mergeFilas(Fila *f1, Fila *f2, Fila *resultado) {
    while (!filaVaziaa(f1) && !filaVaziaa(f2)) {
        if (frente(f1) <= frente(f2)) {
            emfilera(resultado, remove_Fila(f1));
        } else {
            emfilera(resultado, remove_Fila(f2));
        }
    }

    // Adiciona os restantes de f1
    while (!filaVaziaa(f1)) {
        emfilera(resultado, remove_Fila(f1));
    }

    // Adiciona os restantes de f2
    while (!filaVaziaa(f2)) {
        emfilera(resultado, remove_Fila(f2));
    }
}
            


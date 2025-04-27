#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h" //inclui os Prot�tipos


//Defini��o do tipo Fila
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;
//Defini��o do N� Descritor da Fila
struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};



// Definição do tipo de Fila de Fila (Fila de Filas)
struct fila_de_filas {
    Fila* fila;           // Fila individual
    struct fila_de_filas* prox;  // Ponteiro para a próxima fila na fila de filas
};
typedef struct fila_de_filas FilaDeFilas;

FilaDeFilas* cria_fila_de_filas() {
    return NULL;  // Fila de filas vazia inicialmente
}



Fila* cria_Fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    if(fi != NULL){
        Elem* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int consulta_Fila(Fila* fi, struct aluno *al){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    *al = fi->inicio->dados;
    return 1;
}

int insere_Fila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if(fi->final == NULL)//fila vazia
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)//fila ficou vazia
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    return fi->qtd;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)
        return 1;
    if(fi->inicio == NULL)
        return 1;
    return 0;
}

int Fila_cheia(Fila* fi){
    return 0;
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)
        return;
    Elem* no = fi->inicio;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
}


int separa(Fila* f1, Fila* f2, int matricula_n) {
    if (f1 == NULL || f2 == NULL || f1->inicio == NULL) return 0; // filas vazias
    //inicializa os nos das filas
    Elem* atual = f1->inicio;
    Elem* anterior = NULL;

    while (atual != NULL && atual->dados.matricula != matricula_n) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        // Não encontrou a matrícula
        return 0;
    }

    // O nó com a matrícula foi encontrado
    // A fila f2 deve começar no próximo nó
    f2->inicio = atual->prox;
    f2->final = f1->final;

    // Atualiza o final de f1
    atual->prox = NULL;
    f1->final = atual;

    // Atualiza quantidades
    // Primeiro, contamos quantos elementos estão em cada fila
    int count_f1 = 0;
    Elem* temp = f1->inicio;
    while (temp != NULL) {
        count_f1++;
        temp = temp->prox;
    }
    int count_f2 = 0;
    temp = f2->inicio;
    while (temp != NULL) {
        count_f2++;
        temp = temp->prox;
    }
    f1->qtd = count_f1;
    f2->qtd = count_f2;

    return 1; // Sucesso
}




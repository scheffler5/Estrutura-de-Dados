#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista n�o vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e �nico
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
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
// EX 1 -------------------------------------------------------------------------------------
// Esta função é projetada para remover um aluno da lista duplamente encadeada.
// Ela localiza o aluno com base na matrícula fornecida e, caso o encontre,
// ajusta os ponteiros dos nós adjacentes e libera a memória do nó removido.
void remover_aluno(Lista* li, int matricula){
    if(li == NULL || *li == NULL) return;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != matricula){
        no = no->prox;}
    if(no == NULL) return; 
    if(no->ant == NULL){ 
        *li = no->prox;
        if(no->prox != NULL)
            no->prox->ant = NULL;
    } else if(no->prox == NULL){ 
        no->ant->prox = NULL;
    } else { 
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;}
        free(no);}
// EX 2 ------------------------------------------------------------------------------------
// A função 'insere_lista_ordenada' adiciona um novo aluno à lista,
// mantendo a ordem crescente de matrículas. Ela encontra a posição correta
// para o novo aluno e ajusta os ponteiros para realizar a inserção.
int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = al;
    if((*li) == NULL){ 
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    } else {
        Elem *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            atual = atual->prox;}
        if(atual == *li){ 
            no->prox = *li;
            no->ant = NULL;
            (*li)->ant = no;
            *li = no;
        } else if(atual == NULL){ 
            Elem *ultimo = *li;
            while(ultimo->prox != NULL)
                ultimo = ultimo->prox;
            ultimo->prox = no;
            no->ant = ultimo;
            no->prox = NULL;
        } else { 
            no->prox = atual;
            no->ant = atual->ant;
            atual->ant->prox = no;
            atual->ant = no;}
        return 1;}}
// EX 3 --------------------------------------------------------------------------------------------
// Esta função tem como finalidade contar o número de alunos na lista
// que possuem um valor específico para a primeira nota (n1).
// Ela percorre a lista e incrementa um contador para cada correspondência encontrada.
int conta_lista_nota(Lista* li, float n1) {
    if (li == NULL || *li == NULL) return 0;
    int cont = 0;
    Elem* no_atual = *li; 
    while (no_atual != NULL) {
        if (no_atual->dados.n1 == n1)
            cont++;
        no_atual = no_atual->prox;}
    return cont;}
//EX 4 ----------------------------------------------------------------------------------------------
// As funções a seguir implementam operações para uma lista duplamente encadeada circular.
// Isso inclui inserção e remoção no início e no final da lista, além de uma função
// de impressão que percorre a estrutura circularmente.
int insere_lista_inicioc(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = al;
    if(*li == NULL){ 
        no->prox = no;
        no->ant = no;
        *li = no;
    }else{
        Elem* ultimo = (*li)->ant; 
        no->prox = *li;
        no->ant = ultimo;
        ultimo->prox = no;
        (*li)->ant = no;
        *li = no; }
    return 1;}
int insere_lista_finalc(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if (*li == NULL) { // Lista vazia
        no->prox = no;
        no->ant = no;
        *li = no; 
    } else { 
        Elem* ultimo = (*li)->ant; 
        no->prox = *li;            
        no->ant = ultimo;          
        ultimo->prox = no;         
        (*li)->ant = no;           }
    return 1;}
int remove_lista_inicioc(Lista* li){
    if(li == NULL || *li == NULL) return 0; 
    Elem* no_removido = *li;
    if(no_removido->prox == no_removido){ 
        free(no_removido);
        *li = NULL;
    }else{
        Elem* ultimo = no_removido->ant;
        *li = no_removido->prox; 
        ultimo->prox = *li;      
        (*li)->ant = ultimo;     
        free(no_removido);}
    return 1;}
int remove_lista_finalc(Lista* li){
    if(li == NULL || *li == NULL) return 0; 
    Elem* ultimo = (*li)->ant; 
    if(ultimo == *li){ 
        free(ultimo);
        *li = NULL;
    }else{
        Elem* penultimo = ultimo->ant;
        penultimo->prox = *li;     
        (*li)->ant = penultimo;    
        free(ultimo);}
    return 1;}
void imprime_lista_circular(Lista* li){
    if(li == NULL || *li == NULL) return; 
    Elem* no_atual = *li;
    do{
        printf("Matricula: %d\n", no_atual->dados.matricula);
        printf("Nome: %s\n", no_atual->dados.nome);
        printf("Notas: %f %f %f\n", no_atual->dados.n1, no_atual->dados.n2, no_atual->dados.n3);
        printf("-------------------------------\n");
        no_atual = no_atual->prox;
    }while(no_atual != *li); }
//EX 5 ---------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncad.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elemento;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elemento* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        *li = no;
    }else{
        Elemento *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento* no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//n�o encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li))//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elemento* no = *li;
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
    Elemento* no = *li;
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
//Ex 1 -------------------------------------------------------------------------------------------------------------------------------
//EX 1 --- A
int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elemento *no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL)
        return 0; 
    *al = no->dados;
    return 1;}


//EX 1 -- B
int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0) return 0;
    Elemento *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;}
    if(no == NULL) return 0; 
    *al = no->dados;
    return 1; }



//EX 2  -------------------------------------------------------------------------------------------------------------------------------
int remove_recursivo(Elemento** li, int mat){
    if(*li == NULL) return 0;
    if((*li)->dados.matricula == mat){
        Elemento* temp = *li;
        *li = (*li)->prox;
        free(temp);
        return 1;}
    return remove_recursivo(&(*li)->prox, mat);}

int listas_iguais_rec(Elemento* li1, Elemento* li2){
    if(li1 == NULL && li2 == NULL) return 1;
    if(li1 == NULL || li2 == NULL) return 0; 
    if(li1->dados.matricula != li2->dados.matricula ||
       strcmp(li1->dados.nome, li2->dados.nome) != 0 ||
       li1->dados.n1 != li2->dados.n1 ||
       li1->dados.n2 != li2->dados.n2 ||
       li1->dados.n3 != li2->dados.n3)
        return 0; 
    return listas_iguais_rec(li1->prox, li2->prox);}

//EX 3  -------------------------------------------------------------------------------------------------------------------------------
int insere_lista_pos(Lista* li, struct aluno al, int pos) {
    if (li == NULL || pos < 0) { return 0;}
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if (no == NULL) return 0;
    no->dados = al;
    if (pos == 0) { 
        no->prox = *li;
        *li = no;
        return 1;}
    int i = 0;
    Elemento* aux = *li;
    while (aux != NULL && i < pos - 1) {
        aux = aux->prox;
        i++;}
    if (aux == NULL) {
        free(no);
        return 0;}
    no->prox = aux->prox;
    aux->prox = no;
    return 1;}


//Ex 4  -------------------------------------------------------------------------------------------------------------------------------
ListaValor cria_lista_valores(float v[], int n){
    ListaValor lista = NULL;
    Valor* novo, *ultimo = NULL;
    for(int i = 0; i < n; i++){
        novo = (Valor*) malloc(sizeof(Valor));
        if(novo == NULL) return lista;
        novo->info = v[i];
        novo->prox = NULL;
        if(lista == NULL){
            lista = novo;
        } else {
            ultimo->prox = novo;}
        ultimo = novo;}
    return lista;}

void imprime_lista_valores(ListaValor lista){
    Valor* atual = lista;
    while(atual != NULL){
        printf("%.2f -> ", atual->info);
        atual = atual->prox;
    }
    printf("NULL\n");}

//Ex 5  -------------------------------------------------------------------------------------------------------------------------------
int remove_numero_lista(Lista* li, int mat) {
    if (lista_vazia(li) || mat < 0) return 0;
    Elemento* no = *li;
    while (no != NULL) {
        if (no->dados.matricula == mat) {
            remove_lista(li, mat);}
        no = no->prox;}
    return 1;}

//Ex 6  -------------------------------------------------------------------------------------------------------------------------------
void concatena_listas(Lista* L1, Lista* L2) {
    if (L1 == NULL || L2 == NULL) return;
    if (*L1 == NULL) {
        *L1 = *L2;  
    } else {
        Elemento* aux = *L1;
        while (aux->prox != NULL) {
            aux = aux->prox; }
        aux->prox = *L2;  }
    *L2 = NULL;  }

//Ex 7  -------------------------------------------------------------------------------------------------------------------------------
void remove_repetidos(Lista* li) {
    if (li == NULL || *li == NULL) return;
    Elemento *atual = *li;
    while (atual != NULL) {
        Elemento *anterior = atual;
        Elemento *comparador = atual->prox;
        while (comparador != NULL) {
            if (comparador->dados.matricula == atual->dados.matricula) {
                anterior->prox = comparador->prox;
                free(comparador);
                comparador = anterior->prox;
            } else{
                anterior = comparador;
                comparador = comparador->prox;}}
        atual = atual->prox;}}
#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prot�tipos
#include <stdbool.h>
struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento j� existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 � o n� anterior a r na ordem e-r-d
    // no1 � o pai de no2
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

int totalfolha(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL)  return 0;
    if((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        return 1;
    return totalNO_folha(&((*raiz)->esq)) + totalNO_folha(&((*raiz)->dir));}
// Nesta função ele verifica se a cabeça da arvora esta vazia, depois verifica se raiz->esq e 
//raiz->dir esta null dizendo que é uma folha, depois retorna a recursividade



void imprime_arvore_detalhada(ArvBin *raiz){
    printf("--- Estrutura da Arvore ---\n");
    if(raiz == NULL || *raiz == NULL){
        printf("Arvore vazia.\n");
        return;}
    imprime_arvore_detalhada_rec(*raiz, 0);
    printf("---------------------------\n");}


void imprime_arvore_detalhada_rec(struct NO* no, int nivel) {
    if (no == NULL) return;
    for (int i = 0; i < nivel; i++) {
        printf("    "); }
    printf("-> %d", no->info);
    if (no->esq == NULL && no->dir == NULL) {
        printf(" (Folha)\n");
    } else {
        if (no->esq != NULL) printf(" [E: %d]", no->esq->info);
        if (no->dir != NULL) printf(" [D: %d]", no->dir->info);
        printf("\n");}
    imprime_arvore_detalhada_rec(no->esq, nivel + 1);
    imprime_arvore_detalhada_rec(no->dir, nivel + 1);}
    //A funçao imprimir_arvore_detalhada_rec é uma função auxiliar de imprime_arvore_detalhada, nesta função ele apenas vai printar a segmentação de nos da arvore
    //na verfifcação ele imprime Folha e se nao ele mostra quais sao os filhos de cada pai, deizendo se esta a esquerda ou direita
    //a função recursiva é acionada indo para esquerda e depois os ramos a direita, e depois voltando, dessa forma ela sobe um nivel para espaço
    // no final ela deve ficar da seguinte forma por exemplo
/*
--- Estrutura da Arvore ---
-> 50 [E: 30] [D: 90]
    -> 30 [E: 20] [D: 40]
        -> 20 (Folha)
        -> 40 (Folha)
    -> 90 [D: 98]
        -> 98 [E: 94]
            -> 94 (Folha)
---------------------------
*/



int conta_ocorrencias(ArvBin *raiz, int valor) {
    if (raiz == NULL || *raiz == NULL) return 0;
    return conta_ocorrencias_rec(*raiz, valor);}

int conta_ocorrencias_rec(struct NO* no, int valor) {
    if (no == NULL) return 0;
    int contador = 0;
    if (no->info == valor) contador = 1;
    return contador + conta_ocorrencias_rec(no->esq, valor) + conta_ocorrencias_rec(no->dir, valor);}
//Esta função conta_ocorrencias_rec serve como auxiliar de conta_ocorrencias, nesta função ele tem um contador que incrementa quando um 
// valor pre determinado atende ao numero inputado, ele entra na função recursiva novamente ate ir em toda a arvore


void imprime_folhas_decrescente(ArvBin *raiz) {
    printf("Nós folhas em ordem decrescente: ");
    if (raiz == NULL || *raiz == NULL) {
        printf("[arvore vazia]\n");
        return;}
    imprime_folhas_decrescente_rec(*raiz);
    printf("\n");}

void imprime_folhas_decrescente_rec(struct NO* no) {
    if (no == NULL) return;
    imprime_folhas_decrescente_rec(no->dir);
    if (no->esq == NULL && no->dir == NULL) printf("%d ", no->info); 
    imprime_folhas_decrescente_rec(no->esq);}

//novamente a função rec funciona como aux, como o funcionamento da arvore ja funciona 'ordenando' os valores, ela deve pegar primeiramente os valores a direita
// depois que printar o valor mais a direita, vai voltando com os valores da esquerda no ramo da direita, pegando os valores do maior para o menor



bool sao_iguais(ArvBin *raiz1, ArvBin *raiz2) {
    return sao_iguais_rec(*raiz1, *raiz2);}

bool sao_iguais_rec(struct NO* no1, struct NO* no2) {
    if (no1 == NULL && no2 == NULL) return true;
    if (no1 == NULL || no2 == NULL) return false;
    return (no1->info == no2->info &&
            sao_iguais_rec(no1->esq, no2->esq) &&
            sao_iguais_rec(no1->dir, no2->dir));}
// na função rec ele apenas compara cada ramo da arvore e no final se forem iguais ela retorna true ou false para igual ou nao, esta função é bem simples
//ele compara tanto a direita, quanto a esquerda e retorna na função recursiva



void elimina_pares(ArvBin* raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    int tamanho_max = totalNO(raiz);
    if (tamanho_max == 0) return;
    int* pares_a_remover = (int*)malloc(tamanho_max * sizeof(int));
    if (pares_a_remover == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;}
    int num_pares = 0;
    coletar_valores_pares_rec(*raiz, pares_a_remover, &num_pares);
    printf("Removendo %d valores pares...\n", num_pares);
    for (int i = 0; i < num_pares; i++) {
        printf("Removendo o no: %d\n", pares_a_remover[i]);
        remove_ArvBin(raiz, pares_a_remover[i]);}
    free(pares_a_remover);}

void coletar_valores_pares_rec(struct NO* no, int* lista, int* contador) {
    if (no == NULL) return;
    if (no->info % 2 == 0) {
        lista[*contador] = no->info; 
        (*contador)++;}
    coletar_valores_pares_rec(no->esq, lista, contador);
    coletar_valores_pares_rec(no->dir, lista, contador);}

// estas duas funçoes encontrar um numero par, coletam ele colocando em uma lista com o indice pelo contador, depois na outra função
// ele cria um vetor, pega o numero do contador e insere o vetor  como a lista em rec, depois ele da um free() nos pares que sobram


bool sao_similares(ArvBin *raiz1, ArvBin *raiz2) {
    return sao_similares_rec(*raiz1, *raiz2);}

bool sao_similares_rec(struct NO* no1, struct NO* no2) {
    if (no1 == NULL && no2 == NULL) return true;
    if (no1 == NULL || no2 == NULL) return false;
    return sao_similares_rec(no1->esq, no2->esq) &&
           sao_similares_rec(no1->dir, no2->dir);}

// eu utilizo um pensamento parecido do exercicio se arvores sao iguais, mas dessa vez eu nao comparo os valores e sim como é a estrutura da arvore
// com seus respectivos ramos e etc




void imprime_arvore_char_rec(struct NO* no, int nivel) {
    if (no == NULL) return;
    for (int i = 0; i < nivel; i++) printf("    ");
    printf("-> %c", no->info); 
    if (no->esq == NULL && no->dir == NULL) {
        printf(" (Folha)\n");
    } else {
        if (no->esq != NULL) printf(" [E: %c]", no->esq->info);
        if (no->dir != NULL) printf(" [D: %c]", no->dir->info);
        printf("\n");}
    imprime_arvore_char_rec(no->esq, nivel + 1);
    imprime_arvore_char_rec(no->dir, nivel + 1);}

void imprime_arvore_char_detalhada(ArvBin *raiz) {
    printf("--- Estrutura da Arvore ---\n");
    if (raiz == NULL || *raiz == NULL) {
        printf("Arvore vazia.\n");
        return;}
    imprime_arvore_char_rec(*raiz, 0);
    printf("---------------------------\n");}

void preOrdem_char_rec(struct NO* no) {
    if (no == NULL) return;
    printf("%c ", no->info);
    preOrdem_char_rec(no->esq);
    preOrdem_char_rec(no->dir);}

void emOrdem_char_rec(struct NO* no) {
    if (no == NULL) return;
    emOrdem_char_rec(no->esq);
    printf("%c ", no->info);
    emOrdem_char_rec(no->dir);}

void posOrdem_char_rec(struct NO* no) {
    if (no == NULL) return;
    posOrdem_char_rec(no->esq);
    posOrdem_char_rec(no->dir);
    printf("%c ", no->info);}

void imprime_percursos(ArvBin* raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    printf("Pre-Ordem (Raiz, Esq, Dir): ");
    preOrdem_char_rec(*raiz);
    printf("\n");
    printf("Em-Ordem  (Esq, Raiz, Dir): ");
    emOrdem_char_rec(*raiz);
    printf("\n");
    printf("Pos-Ordem (Esq, Dir, Raiz): ");
    posOrdem_char_rec(*raiz);}

//nessas funçoes copiadas do arquivo e alteradas para char. eu tambem ordeno eles da forma como solicitada nas fnçoes pos, em e pre ordem
//este exercicio foi mais tranquilo porem extenso pois apenas tive que readaptar as funçoes para char

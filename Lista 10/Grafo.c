#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h" //inclui os Prot�tipos
#include <limits.h> // Para usar INT_MAX
#include <stdbool.h> // Para usar o tipo bool

//Defini��o do tipo Grafo
struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};
/* Aloca dinamicamente a memória para um grafo representado por lista de adjacências,
 com base no número de vértices e grau máximo informados. A função inicializa as
 estruturas necessárias, incluindo pesos se for ponderado, e retorna um ponteiro para o grafo

 */
Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0)?1:0;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i=0; i<nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->eh_ponderado){
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
            for(i=0; i<nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}
/*


 Desaloca completamente um grafo da memória, liberando suas estruturas internas
 na ordem inversa da criação. Libera as listas de arestas, pesos (se houver),
 o vetor de graus e, finalmente, a própria estrutura do grafo para evitar vazamentos


*/
void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(i=0; i<gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}
/*

 Insere uma aresta entre uma origem e um destino, após validar os vértices.
 a conexão é adicionada ao final da lista de adjacências da origem, com seu
 peso se o grafo for ponderado. Se não for um dígrafo (eh_digrafo == 0),
 a função se chama recursivamente para criar a aresta no sentido oposto.
 */
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}
/*

 Remove uma aresta de um vértice de origem para um de destino, retornando 0 se não
 for encontrada. A remoção é otimizada: a aresta a ser removida é substituída
 pela última da lista de adjacências, e o grau da origem é decrementado. Se não
 for um dígrafo, a função também remove a conexão no sentido inverso.
 */

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0;
    while(i<gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if(i == gr->grau[orig])//elemento nao encontrado
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if(gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if(eh_digrafo == 0)
        removeAresta(gr,dest,orig,1);
    return 1;
}

void imprime_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->nro_vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            if(gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}
//EX 1 - B ---------------------------------------------------------------------------------------------------
void grafo1a(){
    Grafo* gf = cria_Grafo(8,6,0);
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 0, 2, 0, 0);
    insereAresta(gf, 0, 3, 0, 0);
    insereAresta(gf, 0, 4, 0, 0);
    insereAresta(gf, 0, 5, 0, 0);
    insereAresta(gf, 0, 6, 0, 0);
    insereAresta(gf, 1, 2, 0, 0);
    insereAresta(gf, 1, 3, 0, 0);
    insereAresta(gf, 1, 4, 0, 0);
    insereAresta(gf, 2, 4, 0, 0);
    insereAresta(gf, 2, 6, 0, 0);
    insereAresta(gf, 3, 7, 0, 0);
    imprime_Grafo(gf);
    libera_Grafo(gf);}

void grafo1b(){
    Grafo* gf = cria_Grafo(8,5,0);
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 0, 2, 0, 0);
    insereAresta(gf, 0, 3, 0, 0);
    insereAresta(gf, 0, 4, 0, 0);
    insereAresta(gf, 0, 5, 0, 0);
    insereAresta(gf, 1, 4, 0, 0);
    insereAresta(gf, 1, 5, 0, 0);
    insereAresta(gf, 1, 6, 0, 0);
    insereAresta(gf, 1, 7, 0, 0);
    insereAresta(gf, 2, 4, 0, 0);
    insereAresta(gf, 2, 5, 0, 0);
    insereAresta(gf, 2, 6, 0, 0);
    insereAresta(gf, 2, 7, 0, 0);
    insereAresta(gf, 3, 6, 0, 0);
    insereAresta(gf, 3, 7, 0, 0);
    imprime_Grafo(gf);
    libera_Grafo(gf);}


//EX 1 A - -----------------------------------------------------------------------------------------------------
void grafoDirec(){
    Grafo* gf = cria_Grafo(4, 4, 0);
    insereAresta(gf, 0, 1, 1, 0);
    insereAresta(gf, 1, 2, 1, 0);
    insereAresta(gf, 2, 3, 1, 0);
    imprime_Grafo(gf);
    libera_Grafo(gf);}


void grafonaoDirec(){
    Grafo* gf = cria_Grafo(4, 4, 0);
    insereAresta(gf, 0, 1, 0, 0);
    insereAresta(gf, 1, 2, 0, 0);
    insereAresta(gf, 2, 3, 0, 0);
    imprime_Grafo(gf);
    libera_Grafo(gf);}

//EX 4 --------------------------------------------------------------------------------------------------------
/*
 Define um nó para uma lista de adjacências em um grafo. Cada nó representa
 uma aresta, armazenando o vértice de destino (vizinho), o peso da aresta,
 e um ponteiro (prox) para a próxima aresta na lista do mesmo vértice de origem.
 */
typedef struct Lista {
    int vizinho;
    int peso;
    struct Lista *prox;
} Lista;

/*
 Define a estrutura de um grafo usando uma lista de adjacências. Armazena a
 contagem de nós e arestas, e um vetor (`vet`) onde cada elemento `vet[i]`
 é um ponteiro para a lista encadeada de vizinhos do vértice `i`.
 */
typedef struct {
    int nos;      
    int arestas;  
    Lista **vet;  
} Grafo2;

/*
 Aloca dinamicamente um grafo com `nos` vértices, representado por lista de
 adjacências. A função inicializa as arestas como zero e aponta a cabeça de
 cada lista de vizinhos para NULL, retornando o grafo pronto para uso.
 */

Grafo* cria_grafo2(int nos) {
    Grafo2 *G = (Grafo2*) malloc(sizeof(Grafo2));
    if (G == NULL) return NULL;
    G->nos = nos;
    G->arestas = 0;
    G->vet = (Lista**) malloc(nos * sizeof(Lista*));
    if (G->vet == NULL) {
        free(G);
        return NULL;}
    for (int i = 0; i < nos; i++) {
        G->vet[i] = NULL;}
    return G;}


/*
 Insere uma aresta direcionada do vértice `u` para o `v` com o `peso` especificado.
 A função adiciona o novo nó no início da lista de adjacências de `u`, uma
 operação de tempo constante (O(1)). Para um grafo não-dirigido, a aresta
 de volta (`v` -> `u`) deve ser inserida em uma chamada separada.
 */
void insere_aresta2(Grafo2 *G, int u, int v, int peso) {
    if (G == NULL || u < 0 || u >= G->nos || v < 0 || v >= G->nos) return; 
    Lista *novoNo = (Lista*) malloc(sizeof(Lista));
    if (novoNo == NULL) return;
    novoNo->vizinho = v;
    novoNo->peso = peso;
    novoNo->prox = G->vet[u];
    G->vet[u] = novoNo;
    G->arestas++;}


    /*
 Remove a aresta direcionada do vértice `u` para o `v`, retornando 1 em caso de
 sucesso e 0 se a aresta não existir. A função percorre a lista de adjacências
 de `u` e, ao encontrar a aresta, ajusta os ponteiros para removê-la da lista
 e liberar sua memória. A aresta de volta (`v` -> `u`) não é afetada.


 */

int remove_aresta2(Grafo2 *G, int u, int v) {
    if (G == NULL || u < 0 || u >= G->nos || v < 0 || v >= G->nos) return 0;
    Lista *atual = G->vet[u];
    Lista *anterior = NULL;
    while (atual != NULL && atual->vizinho != v) {
        anterior = atual;
        atual = atual->prox;}
    if (atual != NULL) {
        if (anterior == NULL) { 
            G->vet[u] = atual->prox;
        } else { 
            anterior->prox = atual->prox;}
        free(atual);     
        G->arestas--; 
        return 1;}
    return 0; }

    
/*
 Libera de forma segura toda a memória alocada para um grafo e suas listas.
 A função desaloca cada nó das listas de adjacências, depois o vetor que as
 armazena e, por fim, a própria estrutura do grafo. Ao receber um ponteiro
 duplo, anula o ponteiro original no chamador para prevenir uso indevido.
 */

void libera_grafo2(Grafo2 **G_ptr) {
    if (G_ptr == NULL || *G_ptr == NULL) return;
    Grafo2* G = *G_ptr;
    for (int i = 0; i < G->nos; i++) {
        Lista *atual = G->vet[i];
        while (atual != NULL) {
            Lista *temp = atual;
            atual = atual->prox;
            free(temp);}}
    free(G->vet);
    free(G);
    *G_ptr = NULL;}

/*
 Implementa o algoritmo de Prim para encontrar a Árvore Geradora Mínima (AGM)
 A partir de um nó inicial, constrói a árvore de forma gulosa, sempre adicionando
 a aresta mais barata para um vértice ainda não visitado. A função imprime a AGM
 e retorna um vetor `parente` que a descreve (deve ser liberado pelo chamador)
 */
int* prim(Grafo2* grafo, int inicio) {
    if(grafo == NULL) return NULL;
    if(inicio < 0 || inicio >= grafo->nos) return NULL;
    int i, j, verticeAtual, vizinho;
    int menorPeso;
    int* parente = (int*)malloc(grafo->nos * sizeof(int));
    int* custo = (int*)malloc(grafo->nos * sizeof(int));
    bool* incluidoNaAGM = (bool*)malloc(grafo->nos * sizeof(bool));
    for(i = 0; i < grafo->nos; i++) {
        parente[i] = -1;
        custo[i] = INT_MAX;
        incluidoNaAGM[i] = false;}
    custo[inicio] = 0;
    for(i = 0; i < grafo->nos; i++) {
        verticeAtual = -1;
        menorPeso = INT_MAX;
        for(j = 0; j < grafo->nos; j++) {
            if(!incluidoNaAGM[j] && custo[j] < menorPeso) {
                verticeAtual = j;
                menorPeso = custo[j];}}
        if(verticeAtual == -1) break;
        incluidoNaAGM[verticeAtual] = true;
        Lista* adj = grafo->vet[verticeAtual];
        while(adj != NULL){
            vizinho = adj->vizinho;
            if(!incluidoNaAGM[vizinho] && adj->peso < custo[vizinho]) {
                parente[vizinho] = verticeAtual;
                custo[vizinho] = adj->peso;}
            adj = adj->prox;}}
    printf("\n--- Arvore Geradora Minima (Algoritmo de Prim) ---\n");
    printf(" Aresta | Peso\n");
    int custo_total = 0;
    for (i = 0; i < grafo->nos; i++) {
        if (parente[i] != -1) {
            printf("  %d - %d   | %d\n", parente[i], i, custo[i]);
            custo_total += custo[i];}}
    printf(" Custo Total da AGM: %d\n", custo_total);
    free(custo);
    free(incluidoNaAGM);
    return parente;}
    

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para usar INT_MAX
#include <stdbool.h> // Para usar o tipo bool

typedef struct grafo Grafo;
typedef struct Lista;
typedef struct grafo Grafo2;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
Grafo* cria_grafo2(int nos);
void libera_Grafo(Grafo* gr);
void libera_grafo2(Grafo2 **G_ptr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
void insere_aresta2(Grafo2 *G, int u, int v, int peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);
int remove_aresta2(Grafo2 *G, int u, int v);
void imprime_Grafo(Grafo *gr);

void grafo1a();
void grafo1b();


void grafoDirec();
void grafonaoDirec();


int* prim(Grafo2* grafo, int inicio);
int encontra_menor_aresta(Grafo2 *G, int *origem, int *destino, int *peso);
int encontra_no(Grafo2 *G, int no);


// Funçoes extras...
void dfs_recursivo(Grafo2 *G, int vertice, bool *visitado);
int busca_profundidade(Grafo2 *G, int inicio);
int grafo_conectado(Grafo2 *G);
int dfs_caminho_recursivo(Grafo2 *G, int atual, int destino, bool *visitado, int *caminho, int *tamanho_caminho);
int encontra_caminho(Grafo2 *G, int origem, int destino);

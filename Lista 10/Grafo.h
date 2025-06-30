//Arquivo Grafo.h

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

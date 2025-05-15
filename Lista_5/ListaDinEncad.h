//Arquivo ListaDinEncad.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Lista;
struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elemento;

struct valor {
    float info;
    struct valor *prox;
};
typedef struct valor Valor;
typedef Valor* ListaValor;

Lista* cria_lista();

void libera_lista(Lista* li);

int insere_lista_final(Lista* li, struct aluno al);

int insere_lista_inicio(Lista* li, struct aluno al);

int insere_lista_ordenada(Lista* li, struct aluno al);

int remove_lista(Lista* li, int mat);

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);

int tamanho_lista(Lista* li);

int lista_vazia(Lista* li);

int lista_cheia(Lista* li);

void imprime_lista(Lista* li);

int consulta_lista_mat(Lista* li, int mat, struct aluno *al);

int consulta_lista_pos(Lista* li, int pos, struct aluno *al);

int remove_recursivo(Elemento** li, int mat);

int listas_iguais_rec(Elemento* li1, Elemento* li2);

int insere_lista_pos(Lista* li, struct aluno al, int pos);

ListaValor cria_lista_valores(float v[], int n);

void imprime_lista_valores(ListaValor lista);

void concatena_listas(Lista* L1, Lista* L2);

void remove_repetidos(Lista* li);


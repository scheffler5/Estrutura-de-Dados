#ifndef FILADIN_H
#define FILADIN_H
#define TAMANHO 5
// definição do tipo de aluno
struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

// definição do tipo de elemento (para filas e pilhas)
struct elemento {
    struct aluno dados;
    int num;
    struct elemento *prox;
};
typedef struct elemento Elem;

// Definição do tipo Fila
struct fila {
    float itens[TAMANHO];
    Elem* inicio;
    Elem* final;
    int qtd;
};
typedef struct fila Fila;

struct filadefilas {
    Fila* f1;
    Fila* f2;
    Elem* inicio;
    Elem* final;
    int qtd;
};
typedef struct filadefilas FDF;




// Protótipos das funções
Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
void imprime_Fila(Fila* fi);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int separa(Fila* f1, Fila* f2, int matricula_n);
int emfilera(Fila* fi, int valor);
int filaVaziaa(Fila* f);
int filaCheia(Fila* f);
void FuraFila(Fila* f, struct aluno al);
void percorrerFila(Fila* f);



// Definição de Pilha
struct pilha {
    Elem* topo;
};
typedef struct pilha Pilha;

struct filadepilhas {
    Fila* f3;
    Pilha* p1;
    Pilha* p2;
    Elem* inicio;
    Elem* final;
    int qtd;
};
typedef struct filadepilhas FDP;

struct pilhasdefilas {
    Fila* f1;
    Fila* f2;
    Elem* inicio;
    Elem* final;
    int qtd;
};
typedef struct pilhasdefilas PDF;

// Protótipos das funções de pilha
void inicializarPilha(Pilha* p);
int pilhaVazia(Pilha* p);
int empilhar(Pilha* p, int valor);
int desempilhar(Pilha* p);
void inverterFila(Fila *f);
int filadefilas(Fila* f1, Fila* f2);
int filadepilhas(Fila* f3, Pilha* p1, Pilha* p2);
int pilhasdefilas(Fila* f1, Fila* f2);

typedef struct Aviao {
    int id;
    char modelo[50];
    char companhia[50];
    struct Aviao *prox;
} Aviao;

Aviao* criarAviao();
void adicionarAviao();
void listarNumeroAvioes();
void autorizarDecolagem();
void listarTodosAvioes();
void listarPrimeiroAviao();
void menu();
int frente(Fila *f);
void mergeFilas(Fila *f1, Fila *f2, Fila *resultado);

#endif



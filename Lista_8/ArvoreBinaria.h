#include <stdbool.h>
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);
int totalfolha(ArvBin *raiz);
void imprime_arvore_detalhada_rec(struct NO* no, int nivel);
void imprime_arvore_detalhada(ArvBin *raiz);
int conta_ocorrencias(ArvBin *raiz, int valor);
int conta_ocorrencias_rec(struct NO* no, int valor);
void imprime_folhas_decrescente(ArvBin *raiz);
void imprime_folhas_decrescente_rec(struct NO* no);
bool sao_iguais(ArvBin *raiz1, ArvBin *raiz2);
bool sao_iguais_rec(struct NO* no1, struct NO* no2);
void elimina_pares(ArvBin* raiz);
void coletar_valores_pares_rec(struct NO* no, int* lista, int* contador);
bool sao_similares(ArvBin *raiz1, ArvBin *raiz2);
bool sao_similares_rec(struct NO* no1, struct NO* no2);
void imprime_arvore_char_rec(struct NO* no, int nivel) ;
void imprime_arvore_char_detalhada(ArvBin *raiz);
void preOrdem_char_rec(struct NO* no);
void emOrdem_char_rec(struct NO* no);
void posOrdem_char_rec(struct NO* no);
void imprime_percursos(ArvBin* raiz);


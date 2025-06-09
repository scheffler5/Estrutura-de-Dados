#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prot�tipos

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
    // Validação inicial: se o ponteiro para a árvore for nulo, não é possível inserir.
    if(raiz == NULL)
        return 0;
        // Declara o ponteiro para o novo nó que será inserido na árvore.
    struct NO* novo;
    // Aloca (reserva) o espaço na memória necessário para um nó
    novo = (struct NO*) malloc(sizeof(struct NO));
    // Verifica se a alocação de memória falhou 
    if(novo == NULL)
        return 0;
        // Inicializa os campos do novo nó com os valores passados.
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
// Verifica se a árvore está vazia (*raiz aponta para NULL).
    if(*raiz == NULL)
    // Se a árvore estiver vazia, o novo nó se torna a raiz.
        *raiz = novo;
    else{
        // Se a árvore não estiver vazia, é preciso encontrar o local correto para a inserção.
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        // Loop quando for NULL ele paga 
        while(atual != NULL){
            // iguala o anterioe ao atual
            ant = atual;
            // verifica o valor igual ao atual
            if(valor == atual->info){
                // libera para nao ter valores iguais
                free(novo);
                return 0;
            }
// valor maior que atual ele insere no atual a direita
            if(valor > atual->info)
                atual = atual->dir;
                //se nao, ele insere no atual a esquerda
            else
                atual = atual->esq;
        }
        //se valor for maior que anterios 
        if(valor > ant->info)
        // ele vai para o novo no a direita
            ant->dir = novo;
        else
        // ele vai para o novo no a esquerda
            ant->esq = novo;
    }
    return 1;
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor){
    // Verifica se o ponteiro para a estrutura da árvore é nulo. Se for, não há o que fazer.
    if(raiz == NULL)
        return 0;
     // 'ant' (anterior) vai guardar o nó pai do nó 'atual' durante a busca.
    struct NO* ant = NULL;
    // 'atual' começa na raiz da árvore e será usado para percorrê-la.
    struct NO* atual = *raiz;
    while(atual != NULL){
        // Compara o valor procurado com o valor do nó atual
        if(valor == atual->info){
            /*Se encontrou o valor, o processo de remoção começa.
            A função auxiliar 'remove_atual' é chamada para tratar os casos de remoção
            substituir o nó removido na árvore.*/
            if(atual == *raiz)
                *raiz = remove_atual(atual);
                /*O nó a ser removido é a própria raiz da árvore.
               A raiz da árvore (*raiz) é atualizada com o resultado de remove_atual.*/
                
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                    /*Se 'atual' for o filho da direita, o ponteiro 'dir' do pai é atualizado.*/
                else
                    ant->esq = remove_atual(atual);
                    // Se 'atual' for o filho da esquerda, o ponteiro 'esq' do pai é atualizado.
            }
            return 1;
        }
        /*Se o valor do nó atual não é o que procuramos, continuamos a busca.
        O nó 'ant' passa a apontar para o 'atual', antes de 'atual' avançar.*/
        ant = atual;
        // Segue a propriedade da Árvore de Busca Binária para decidir o próximo passo.
        if(valor > atual->info)
        // Se o valor procurado for maior, a busca continua na subárvore direita.
            atual = atual->dir;
        else
        // Se o valor procurado for menor, a busca continua na subárvore esquerda.
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
    if (raiz == NULL) return 0;
    if (*raiz == NULL) return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL) return;
    if(*raiz != NULL){
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));}}
/*Esta função implementa uma varredura recursiva de pré-ordem em uma árvore binária. 
A sua lógica de operação consiste em primeiro visitar o nó raiz atual, 
imprimindo seu valor na tela. Em seguida, a função chama a si mesma para percorrer 
completamente todos os nós da subárvore esquerda e, somente após esgotar todo o lado esquerdo, 
ela inicia a travessia por toda a subárvore direita.*/

void emOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL)return;
    if (*raiz != NULL) {
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));}}
/*Esta função recursiva percorre a árvore em ordem, visitando primeiro a subárvore esquerda, 
depois o nó raiz e por fim a subárvore direita, exibindo os valores de forma ordenada.*/

void posOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) return;
    if (*raiz != NULL) {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);}}
/*Esta função recursiva de pós-ordem percorre as subárvores esquerda e 
direita antes de finalmente visitar e processar o nó raiz.*/

int totalNO_Arvore(ArvBin *raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    else return 1 + totalNO_Arvore(&((*raiz)->esq)) + totalNO_Arvore(&((*raiz)->dir));}
/*Esta função recursiva calcula o total de nós em uma árvore somando 1 (pelo nó atual) com 
a contagem total de nós de suas subárvores esquerda e direita.*/

int Cons_Arvore(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;
    struct NO* atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info) {
            return 1;}
        if (valor < atual->info) {
            atual = atual->esq; } 
        else {
            atual = atual->dir;}}
    return 0;}
/*Esta função busca iterativamente por um valor, percorrendo a árvore a partir da raiz e movendo-se 
para a esquerda ou direita com base na comparação, até encontrar o elemento ou atingir o fim de um ramo.*/


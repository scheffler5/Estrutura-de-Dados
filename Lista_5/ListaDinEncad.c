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
// Este exercício implementa duas formas de consulta na lista de alunos:
// a primeira busca um aluno pela matrícula e a segunda o busca pela sua posição,
// retornando os dados do aluno em ambos os casos, se ele for encontrado.
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
    return 1;
}

//EX 1 -- B
int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0) return 0;
    Elemento *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL) return 0;
    *al = no->dados;
    return 1;
}

//EX 2  -------------------------------------------------------------------------------------------------------------------------------
// Aqui são apresentadas duas funções que utilizam recursividade:
// uma para remover um aluno da lista com base na matrícula e outra
// para verificar se duas listas de alunos são exatamente iguais.
int remove_recursivo(Elemento** li, int mat){
    if(*li == NULL) return 0;
    if((*li)->dados.matricula == mat){
        Elemento* temp = *li;
        *li = (*li)->prox;
        free(temp);
        return 1;
    }
    return remove_recursivo(&(*li)->prox, mat);
}

int listas_iguais_rec(Elemento* li1, Elemento* li2){
    if(li1 == NULL && li2 == NULL) return 1; // Ambas vazias, são iguais
    if(li1 == NULL || li2 == NULL) return 0; // Uma vazia e outra não, são diferentes
    // Compara os dados do aluno no nó atual
    if(li1->dados.matricula != li2->dados.matricula ||
       strcmp(li1->dados.nome, li2->dados.nome) != 0 || // strncmp seria mais seguro se nome não for sempre null-terminated ou tiver tamanho fixo
       li1->dados.n1 != li2->dados.n1 ||
       li1->dados.n2 != li2->dados.n2 ||
       li1->dados.n3 != li2->dados.n3)
        return 0; // Dados diferentes
    return listas_iguais_rec(li1->prox, li2->prox); // Verifica o restante da lista
}

//EX 3  -------------------------------------------------------------------------------------------------------------------------------
// Esta função é responsável por inserir um novo aluno em uma posição específica
// da lista. Ela navega até a posição anterior à desejada para então
// realizar a inserção, ajustando os ponteiros corretamente.
int insere_lista_pos(Lista* li, struct aluno al, int pos) {
    if (li == NULL || pos < 0) { return 0;} // Posição 0 indica inserção no início
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if (no == NULL) return 0; // Falha na alocação
    no->dados = al;
    if (pos == 0) { // Inserção no início da lista
        no->prox = *li;
        *li = no;
        return 1;
    }
    int i = 0;
    Elemento* aux = *li;
    // Navega até o elemento anterior à posição de inserção
    while (aux != NULL && i < pos - 1) {
        aux = aux->prox;
        i++;
    }
    // Se aux é NULL (posição inválida, além do fim) ou se a lista era vazia e pos > 0
    if (aux == NULL) {
        free(no); // Libera o nó alocado, pois a posição é inválida
        return 0;
    }
    no->prox = aux->prox;
    aux->prox = no;
    return 1;
}

//Ex 4  -------------------------------------------------------------------------------------------------------------------------------
// Este bloco de código introduz funções para manipular uma lista de valores float.
// A primeira cria e popula essa lista a partir de um array de floats,
// enquanto a segunda se encarrega de imprimir os valores contidos na lista.
typedef struct valor { // Supondo a definição de Valor e ListaValor
    float info;
    struct valor *prox;
} Valor;
typedef Valor* ListaValor;

ListaValor cria_lista_valores(float v[], int n){
    ListaValor lista = NULL;
    Valor* novo, *ultimo = NULL;
    for(int i = 0; i < n; i++){
        novo = (Valor*) malloc(sizeof(Valor));
        if(novo == NULL) { // Falha na alocação, retorna a lista como estava
            // Liberar memória já alocada para 'lista' seria uma boa prática aqui
            // em um cenário de falha parcial.
            return lista;
        }
        novo->info = v[i];
        novo->prox = NULL;
        if(lista == NULL){
            lista = novo;
        } else {
            ultimo->prox = novo;
        }
        ultimo = novo;
    }
    return lista;
}

void imprime_lista_valores(ListaValor lista){
    Valor* atual = lista;
    while(atual != NULL){
        printf("%.2f -> ", atual->info);
        atual = atual->prox;
    }
    printf("NULL\n");
}

//Ex 5  -------------------------------------------------------------------------------------------------------------------------------
// O propósito desta função é remover da lista todos os alunos
// que possuem uma matrícula específica. Ela varre a lista e, ao encontrar
// uma correspondência, utiliza 'remove_lista' para efetuar a remoção.
int remove_numero_lista(Lista* li, int mat) {
    if (lista_vazia(li) || mat < 0) return 0; // Embora mat < 0 não seja um problema por si só para a busca.
    Elemento* no_atual = *li;
    Elemento* anterior = NULL;

    while (no_atual != NULL) {
        if (no_atual->dados.matricula == mat) {
            if (anterior == NULL) { // Removendo o primeiro nó
                *li = no_atual->prox;
                free(no_atual);
                no_atual = *li; // Continua a partir do novo primeiro
            } else { // Removendo nó do meio ou fim
                anterior->prox = no_atual->prox;
                free(no_atual);
                no_atual = anterior->prox; // Continua a partir do nó seguinte ao anterior
            }
        } else {
            anterior = no_atual;
            no_atual = no_atual->prox;
        }
    }
    return 1; // Retorna 1 indicando que a operação foi tentada.
}

//Ex 6  -------------------------------------------------------------------------------------------------------------------------------
// Esta função realiza a concatenação de duas listas simplesmente encadeadas (L1 e L2).
// Os elementos de L2 são anexados ao final de L1,
// e L2 é então definida como vazia (apontando para NULL) para evitar duplicação.
void concatena_listas(Lista* L1, Lista* L2) {
    if (L1 == NULL || L2 == NULL) return; // Listas inválidas (ponteiros para ponteiros)
    if (*L2 == NULL) return; // L2 está vazia, nada a concatenar

    if (*L1 == NULL) { // L1 está vazia
        *L1 = *L2;  // L1 agora aponta para o início de L2
    } else {
        Elemento* aux = *L1;
        // Encontra o último elemento de L1
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = *L2; // O último de L1 agora aponta para o início de L2
    }
    *L2 = NULL; // L2 é "esvaziada" (o ponteiro da lista L2 agora é NULL)
}

//Ex 7  -------------------------------------------------------------------------------------------------------------------------------
// O objetivo desta função é eliminar alunos com matrículas duplicadas da lista.
// Para cada aluno, ela verifica os elementos subsequentes e remove aqueles
// que possuem a mesma matrícula, mantendo apenas a primeira ocorrência encontrada.
void remove_repetidos(Lista* li) {
    if (li == NULL || *li == NULL || (*li)->prox == NULL) return; // Lista inválida, vazia ou com um único elemento

    Elemento *atual = *li;
    while (atual != NULL) {
        Elemento *anterior_comparador = atual;
        Elemento *comparador = atual->prox;
        while (comparador != NULL) {
            if (comparador->dados.matricula == atual->dados.matricula) {
                // Remove o nó 'comparador'
                anterior_comparador->prox = comparador->prox;
                free(comparador);
                comparador = anterior_comparador->prox; // Avança para o próximo nó a ser comparado
            } else {
                anterior_comparador = comparador;
                comparador = comparador->prox;
            }
        }
        atual = atual->prox; // Avança para o próximo nó da lista principal
    }
}
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h" //inclui os Prot�tipos

//Defini��o do tipo Pilha
struct elemento{
    struct aluno dados;
    int num;
    struct elemento *prox;
};
typedef struct elemento Elem;



Pilha* cria_Pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

void libera_Pilha(Pilha* pi){
    if(pi != NULL){
        Elem* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int consulta_topo_Pilha(Pilha* pi, struct aluno *al){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    *al = (*pi)->dados;
    return 1;
}

int insere_Pilha(Pilha* pi, struct aluno al){
    if(pi == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int remove_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

int tamanho_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    int cont = 0;
    Elem* no = *pi;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int Pilha_cheia(Pilha* pi){
    return 0;
}

int Pilha_vazia(Pilha* pi){
    if(pi == NULL)
        return 1;
    if(*pi == NULL)
        return 1;
    return 0;
}

void imprime_Pilha(Pilha* pi){
    if(pi == NULL)
        return;
    Elem* no = *pi;
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
void imprime_Pilha2(Pilha* pi){
    if(pi == NULL)
        return;
    Elem* no = *pi;
    while(no != NULL){
        printf("Matricula: %d\n",no->num);
        no = no->prox;
    }
}

//EX 1 e 2
int push2 (Pilha* pi,struct aluno a,int n){
    for (int i=0; i<n;i++){
        if(pi == NULL) return 0;
        Elem* no;
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) return 0;
        no-> dados = a;
        no->prox = (*pi);
        *pi = no;}
    return 1;}
//EX 1 e 2
// eu reutilizei parte da função de remover da pilha para aqui e adicionei um for para a quantidade n
int pop2(Pilha* pi,int n){
    for (int i=0;i<n;i++){
        if(pi == NULL)
            return 0;
        if((*pi) == NULL)
            return 0;
        Elem *no = *pi;
        *pi = no->prox;
        free(no);}
    return 1;}

//EX 3
// nesta função eu coloco como parametro as duas pilhas 
void transferir(Pilha* pi){
    Pilha* p =  cria_Pilha();
    //calculo o tamanho da pilha para posterior for
    int tamanho = tamanho_Pilha(pi);
    //crio o vetor com alocação dinamica
    struct aluno* vetor = (struct aluno*) malloc(tamanho * sizeof(struct aluno));
    // puxo o elemento como ponteiro para pi
    Elem* no = *pi;
    // coloco o i igual ao tamanho pre estabelcido menos 1 para o for de push
    int i = tamanho - 1;
    // while para ele parar quando o no for NULL
    while (no != NULL) {
        // aqui eu povoo o vetor utilizando o i como paramtro para o indice do vetor e puxo o nó dos dados da struct
        vetor[i] = (*pi)->dados;
        // puxo o no para o proximo nó
        no = no->prox;
    }
// for para puxar os dados do vetor para a pilha 2
    for (i = 0; i < tamanho; i++) {
        //puxo os valores do vetor para a pilha com a função ja feita
        push2(p, vetor[i], 1);
    }
    imprime_Pilha(p);
    // printa o tamanho da pilha nova antes do drop
    printf("Tamanho da copia de pilha antes do drop: \n");
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(p));
    // dropa a pilha nova
    pop2(p,tamanho);
    imprime_Pilha(p);
    // imprime o tamanho da pilha depois do drop
    printf("Tamanho da copia de pilha depois do drop: \n");
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(p));
    libera_Pilha(p);
    //libera o vetor
    free(vetor);
    //retorna
    return;
}
//EX4
int numeros(Pilha* pii, int n){
    int numero,maior = 0,menor = 0,soma = 0,media = 0;
    Elem* no;
    for (int i=0; i<n;i++){
        printf("Digite um numero para ser armazenado : ");
        scanf("%d",&numero);
        if(pii == NULL) return 0;
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) return 0;
        no->num = numero;
        no->prox = (*pii);
        *pii = no;}
    int tamanho = tamanho_Pilha(pii);
    while(no != NULL){
        if(maior < no->num){
            maior = no->num;
        }
        if(menor > no->num){
            menor = no->num;
        }
        soma = soma + no->num;
        no = no->prox;
    }
    printf("\nMaior Numero: %d",maior);
    printf("\nMenor numero : %d",menor);
    media = soma/tamanho;
    printf("\nA media : %d\n\n",media);
    imprime_Pilha2(pii);
    return 1;
}
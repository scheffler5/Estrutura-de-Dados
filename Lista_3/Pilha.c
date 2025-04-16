#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h" 
#include <string.h>
#include <ctype.h>

//Defini��o do tipo Pilha
struct elemento{
    struct aluno dados;
    //Variavel da estrutura int para pilhas formato inteiros
    int num;
    //variavel da estrutura char para pilhas formato char
    char palavra;
    // variavel da estrutura int para pilhas formato inteiro
    int numero;
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
void imprime_Pilha3(Pilha* pi){
    if(pi == NULL)
        return;
    Elem* no = *pi;
    while(no != NULL){
        printf("Matricula: %c\n",no->palavra);
        no = no->prox;
    }
}
//EX 1 e 2
int push2 (Pilha* pi,struct aluno a,int n){
    // pego o tamanho da pilha que eu vou inserir
    for (int i=0; i<n;i++){
        // if para pilha == null
        if(pi == NULL) return 0;
        //declara;ao da funcao estrutura
        Elem* no;
        // criacao de vetor com alocacao dinamica
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) return 0;
        // insere os dados de aluno em no
        no-> dados = a;
        // passa para o proximo no
        no->prox = (*pi);
        // tira do vetor e joga na pilha
        *pi = no;}
    return 1;}
//EX 1 e 2
// eu reutilizei parte da função de remover da pilha para aqui e adicionei um for para a quantidade n
int pop2(Pilha* pi,int n){
    // for pegando o tamanho da pilha ser desempilhada
    for (int i=0;i<n;i++){
        if(pi == NULL)
            return 0;
        if((*pi) == NULL)
            return 0;
        // atribui;ao de ponterio de no na pilha pi
        Elem *no = *pi;
        // passa para o proximo no
        *pi = no->prox;
        // libera a memoria do vetor no
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
// Nesta funcao eu verifico o menor numero, o maior e a media da pilha
int numeros(Pilha* pii, int n){
    // declaracao das variaveis
    int numero,maior = 0,menor = 0,soma = 0,media = 0;
    // declaracao do elemento
    Elem* no;
    // for para armazenar os numeros que o usuario disser na pilha, para conferir depois
    for (int i=0; i<n;i++){
        printf("Digite um numero para ser armazenado : ");
        scanf("%d",&numero);
        if(pii == NULL) return 0;
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) return 0;
        no->num = numero;
        no->prox = (*pii);
        *pii = no;

    }
    //atribui o tamanho ao tamanho da pilha pii
    int tamanho = tamanho_Pilha(pii);
    // while para ate quando o no for NULL
    while(no != NULL){
        // Encontra o maior numero 
        if(maior < no->num){
            maior = no->num;
        }
        //encontra o menor numero 
        if(menor > no->num){
            menor = no->num;
        }
        // nesta soma eu somo todos os elementos da pilha e divido pelo tamanho da mesmo --- Media
        soma = soma + no->num;
        no = no->prox;
    }
    // prints finais dos valores
    printf("\nMaior Numero: %d",maior);
    printf("\nMenor numero : %d",menor);
    media = soma/tamanho;
    printf("\nA media : %d\n\n",media);
    imprime_Pilha2(pii);
    return 1;
}
// Funcao para empilhar elementos inteiros
// Nao vou me estender muito na explicacao pois ja foi explicado o funcionamento no EX 1 e 2
int push3(Pilha* piii, int n) {
    int numero;
    Elem* no;
    for (int i=0; i<n;i++){
        printf("Digite um numero para ser armazenado : ");
        scanf("%d",&numero);
        if(piii == NULL) return 0;
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) return 0;
        no->num = numero;
        no->prox = (*piii);
        *piii = no;
    }
    return 1;
}
// Nesta funcao eu verifico se uma pilha eh igual a outra da seguinte forma
int verificar(Pilha* pii, Pilha* piii){
    //verificacao para ver se elas nao sao nulas ja parando logo no inicio
    if (pii == NULL || piii == NULL) {
        printf("Uma das pilhas é nula!\n");
        return 0;
    }
    // chamada das variaveis da estrutura para puxar as pilhas
    Elem* no = *pii;   
    Elem* noo = *piii;
    // ver os tamanhos das pilhas 
    int t1 = tamanho_Pilha(pii);
    int t2 = tamanho_Pilha(piii);
    // verifica os tamanhos, se nao forem iguais ja para 
    if (t1 != t2) {
        printf("As pilhas têm tamanhos diferentes!\n");
        return 0;
    }
    // impressao das pilhas apenas para testes e visualiza;ao dos usuarios
    imprime_Pilha2(piii);
    imprime_Pilha2(pii);
    // while com if para verificar celula por celula da pilha 
    while (noo != NULL && no != NULL) {
        if (noo->num != no->num) {
            printf("As pilhas não são iguais!\n");
            return 0;
        }
        // passa para o proximo no
        noo = noo->prox;
        no = no->prox;
    }
    // print que sao iguais
    printf("As pilhas são iguais!\n");
    return 1;
}
//E6 
//Funcao para empilhar char 
int push4(Pilha* pi,char* str) {
    // declara;ao de numero sendo char e as outras variaveis
    char numero;
    Elem* no;
    int i = 0;
    do {// do while para armazenar o valor impondo algumas condi;oes 
        //input
        printf("Digite um numero para ser armazenado (Digite * para sair): ");
        scanf(" %c", &numero); 
        // quando o user digitar * o programa para 
        if (numero == '*') break; 
        // quando tiver espa;o ou ponto ele continua
        if (numero == ' ' || numero == '.') continue;
        //verificacao de pi === null
        if (pi == NULL) return 0;
        // criacao de vetor 
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) return 0;
        // joga o valor de numero para a pilha 
        no->palavra = tolower(numero);
        // passa para o proximo no 
        no->prox = (*pi);
        // iguala o valor ao ponteiro da pilha 
        *pi = no;
        // aqui ele joga o numero para dentro de um vetor str
        str[i++] = tolower(numero);
    } while (1);
    // adiciona o ultimo valor como /0 ( enter)
    str[i] = '\0';
    return 1;
}
// nesta funcao eu pego o str e confiro na ordem ao contraria da pilha para ver se eh igual
int Palindromo(Pilha* pi, char* str) {
    int i = 0;
    Elem* no = *pi;
    //while para no ate NULL
    while (no != NULL) {
        // if para verficar se a pilha eh igual ao vetor
        if (no->palavra != str[i]) {
            return 0; 
        }
        // passa para o proximo no
        no = no->prox;
        i++;
    }
    return 1; 
}
// funcao para verificar quais numeros da pilha sao pares
int par(Pilha* pi) {
    // pega a pilha e atribui a estrutura ELEM
    Elem* no = *pi;
    printf("Números par na pilha:\n");
    while (no != NULL) {
        // se o no da pilha tiver resto 0 ele eh par
        if (no->num % 2 == 0) {
            printf("%d\n", no->num);
            // dai ele so printa os numeros que sao pares
        }
        // passa para o proximo no
        no = no->prox;
    }
}
// aqui eh uma funcao para ver se eh impar, mesma ideia da funcao de par 
int impar(Pilha* pi) {
    Elem* no = *pi;
    printf("Números ímpares na pilha:\n");
    while (no != NULL) {
        // unica diferenca eh que ele printa quando tiver 0 na divisao por 2
        if (no->num % 2 != 0) {
            printf("%d\n", no->num);
        }
        no = no->prox;
    }
}


// nesta funcao eu verifico se a pilha esta vazia

int vazia(Pilha *p) {
    // verifica se tem ponteiro e valor, se null ele retorna 1
    if (p == NULL || *p == NULL) {
        return 1;  
    }
    return 0;
}
// eu verifico se a pilha esta com coisa dentro
void cheia(Pilha *p) {
    Elem* no = *p;
    // verifica se no no tem numero diferente de 0
    if(no->numero != 0){
        printf("Esta Cheia!");
    }
}
// funcao de empilhar igual do exercicio 1 e 2
void empilhar(Pilha *p, int n) {
    int numero;
    Elem* no = *p;
    for (int i = 0; i < n; i++) {
        printf("Digite um numero para ser armazenado: ");
        scanf("%d", &numero);
        no = (Elem*)malloc(sizeof(Elem));
        if (no == NULL) {
            printf("Erro de alocação de memória!\n");
            return;
        }
        no->numero = numero;
        *p = no;
        no = no->prox;
    }
}
// funcao de desempilhar igual do exercicio 1 e 2
int desempilhar(Pilha *p, int n) {
    Elem *no = *p;
    for (int i=0;i<n;i++){
        if(p == NULL)
            return 0;
        if((*p) == NULL)
            return 1;
        *p = no->prox;
        free(no);}
    return 1;
}
// ele printa o topo da pilha 
void topo(Pilha *p) {
    if(p == NULL)
        return;
    Elem* no = *p;
    // printa o primeiro valor da pilha === topo
    printf("Topo: %d\n",no->numero);
}

// funcao com prints do menu
void menu() 
{ 
printf("1-Verifica se a pilha e vazia.\n"); 
printf("2-Verifica se a pilha e cheia.\n"); 
printf("3-Empilha o elemento na pilha.\n"); 
printf("4-Desempilha elemento da pilha.\n"); 
printf("5-Le topo de um pilha.\n"); 
printf("6-Libera a Pilha\n"); 
printf("7-Sair.\n"); 
}



#include <stdio.h> 
#include <stdlib.h>

//Estrutura de Estoque
struct Estoque {
    int Codigo;
    char Nome_Produto[30];
    float Quantidade;
    float Preco;};

// função de input de valores na estrutura
void Contar(int *t,struct Estoque *e, int index) {
    // if para quando a quantidade de produtos cadastrado forem 0 ele retorna
        if (*t == 0) return;
        else{
            // aqui ele adiciona 1 no Codigo do produto cadastrado de forma imcremental
            e[index].Codigo = index + 1;
            // inputs
            printf("\nDigite o Nome do produto: ");
            scanf("%s", e[index].Nome_Produto);
            printf("\nDigite a Quantidade do produto: ");
            scanf("%f", &e[index].Quantidade);
            printf("\nDigite o Preço do produto: ");
            scanf("%f", &e[index].Preco);
            // diminui 1 do valor de t sem ser do endereço
            (*t)--;
            //aciona a recursividade
            Contar(t, e, index + 1);}}
//função para listar a estrutura
void Listar(int te,struct Estoque *e, int index){
    // if para quando o index que começa em 0 for igual a te ele retorna
     if (index == te) return;
     else{
        // prints pelo numero do indice da estrutura
        printf("Código: %d\n", e[index].Codigo);
        printf("Nome: %s\n", e[index].Nome_Produto);
        printf("Quantidade: %.2f\n", e[index].Quantidade);
        printf("Preço: %.2f\n\n", e[index].Preco);
        // aciona a recursividade adicionando 1 
        Listar(te, e, index + 1);
     }
}


void Vetor(int *p, int tamanho) {
    if (tamanho == 0) return; 
    else{ 
        printf("%d ", p[tamanho - 1]);  
        Vetor(p, tamanho - 1); }}
//Função inversora
int  inverte_vetor(int *V1, int *V2,int t, int maior){
// if para retornar o maior numero apos a recursividade quando tamanho de V1 for zero
    if (t == 0 )return maior;
    else {
// faz o V2 pegar o ultimo numero de V1 igualando-os
        V2[t - 1] = V1[0];
        //If para encontrar o maior numero 
        if (V1[0] > maior) {
            maior = V1[0];}
        // retornar a função recursiva com V1 + 1 para a proxima casa, para encontrar o maior numero do vetor e t - 1 para diminuir t e inverter o vetor
        return inverte_vetor(V1 + 1, V2, t - 1, maior);}}

// Função inversora de char
void inverte_char(char *cptr){
    // if para quando o ponteiro de s estiver no \0 ele retorna, ou seja, no final da 'string'
    if (*cptr == '\0') return;
    else{
        //ele chama a função recursiva e soma um na memoria que pula uma casa para a da frente, e vai pulando nas recursoes ate \0 e la imprime o ultimo caracter
        inverte_char(cptr + 1);
        //imprime o caracter
        printf("%c", *cptr);}}
// Função recursiva para popula o vetor com os inputs
void popular(int n, int *vet,int index){
    // se index 0 for igual a n (tamanho) ele retorna 
    if (index == n)return;
    else{
        //input de valores para o vet
        printf("\nDigite um valor para a posição %d: ", index);
        scanf("%d", &vet[index]);
        // recursividade 
        popular(n, vet, index + 1);}}

        //Função recursiva para impressao do vetor
void imprimir(int n, int *vet, int index) {
    // se o index for igual a n (tamanho) ele retorna
    if (index == n) return;
    else{
        // print da posição no vetor
    printf("%d ", vet[index]);
    //recursividade
    imprimir(n, vet, index + 1);}}



// função recursiva que aloca memoria na matriz


// Função recursiva para preencher a matriz
void preencher(int **matriz, int m, int n, int i, int j) {
    //se i for igual m(Quantidade de colunas) ele retorna 
    if (i == m) return; 
    else{
        // com a mesma ideia para o vetor ele inputa na matriz
        printf("Elemento [%d][%d]: ", i, j);
        scanf("%d", &matriz[i][j]);
        // ele verifica qual linha e coluna ele vai acionar a recursividade
        if (j + 1 < n) {
            preencher(matriz, m, n, i, j + 1);
        }else {
            preencher(matriz, m, n, i + 1, 0);}}}

// função recursiva para imprimir a matriz
void imprimir_matriz(int **matriz, int m, int n, int i, int j) {
    //se i for igual m(Quantidade de colunas) ele retorna 
    if (i == m) return; 
    else{
        // a mesma ideia do vetor mas aqui ele printa a matriz
        printf("%d ", matriz[i][j]);
        // verifica qual coluna ou linha vai continuar a recursividade
        if (j + 1 < n) {
            imprimir_matriz(matriz, m, n, i, j + 1);
        }else {
            printf("\n");
            imprimir_matriz(matriz, m, n, i + 1, 0);}}}

// função recursiva para liberar a memória da matriz


int main()  { 
/*
EX 1 ---------------------------------------------
Incrementa o proximo elemento da memoria, se for char +1byte e int +2bytes
p++;      
Incrementa o proximo valor da posição de p, por exemplo de for um int 1 ele vai para 2
• (*p)++;         
Ele acessa o valor do ponteiro e depois incrementa
• *(p++); 
Ele acessa o pronteiro em uma posição especifica como 10, quando um vetor seria p[10]
• O que quer dizer *(p+10);
*/

// EX 2 ------------------------------------------
//Declara as variaveis e o ponteiro
int y, *p1, x1;  
//Iguala o y igual a zero
y = 0;  
// ponteiro aponta para y
p1 = &y;  
// iguala x a *p que é a mesma coisa que x igual a y
x1 = *p1; 
// iguala x igual a 4 
x1 = 4;  
// incrementa o ponteiro igualado a y = 0 para y = 1
(*p1)++;  
// diminui um valor de x = 4 para x = 3
x1--;  
// soma o *p = y que é y = 1 mais o x= 3 resultando em y = 4 = *p
(*p1) += x1;  
// print do valor de y = 4
printf ("y = %d\n", y); 

// EX 3 -----------------------------------------
int x, *p, **q; 
p = &x; 
q = &p; 
x = 10; 
printf("\n%d\n", **q);
/*O problema encontrado esta no print que o q um ponteiro duplo nao esta apontando de fato o valor
e sim estava arquitetado para mostrar o endereço de memoria, agora ele mostrará o valor 10 */

//EX 4 ------------------------------------------ 
int n1;
printf("\nDigite um numero para o vetor : ");
scanf("%d", &n1);
int V[n1];
for (int i = 0; i < n1; i++) {
    printf("Digite o valor para V[%d]: ", i);
    scanf("%d", &V[i]);}
printf("\nO Vetor com memória alocada: ");
Vetor(V, n1);
/*Neste exercicio eu criei uma função chamada Vetor que armazena o vetor como um ponteiro e pega o tamanho do vetor que é falado pelo
Usuario e adicionado em uma função recursiva que printa as cordenadas da memoria dos vetores*/

//EX 5 -----------------------------------------
//Declara a variavel n que é o tamanho
int n;
// digite o tamanho do vetor V1
printf("\nDigite um numero para o vetor : ");
scanf("%d", &n);
// Alocação Dinamica de memoria para o V1 e V2
int *V1 = (int *)malloc(n * sizeof(int));
int *V2 = (int *)malloc(n * sizeof(int));
// For para inserção de dados em V1
for (int i = 0; i < n; i++) {
    printf("Digite o valor para V[%d]: ", i);
    scanf("%d", &V1[i]);}
// função Recursiva passando os parametros
int maior = inverte_vetor(V1, V2, n, V1[0]);
printf("\nVetor invertido (V2): ");
//For para mostrar o vetor invertido V2
    for (int i = 0; i < n; i++) {
        printf("%d ", V2[i]);
    }
    // Mostra o maior valor de V1
printf("\nMaior valor encontrado em V1: %d\n", maior);
// Libera a memoria 
free(V1);
free(V2);
/* Neste Exercicio eu inverti V1 e inseri invertido em V2 da seguinte forma, eu primeiro dei um tamanho em n no main,
depois eu aloquei a memoria para inicializar o ponteiro e inseri valores em V1, depois eu ativei a função recursiva, para 
inverter os valores eu fiz um if para retornar o maior numero e no else eu pego o V2 e dou o mesmo tamanho menos 1 de V1 e assimilo 
a ele o primeiro valor de V1, isto se extende ate t = 0 na recursividade, quando ele retorna o vetor v2 e o maior numero*/

//EX 6 ----------------------------------------
// Declaração de variavel
char s[10] = "abcde"; 
// atribuição de ponteiro com o mesmo apontando para s
char *cptr = s;
printf("\nString invertida : ");
//Chamada da função recursiva de inversao de char
inverte_char(cptr);
/*Nesta função eu peguei a variavel s e apontei um ponteiro cptr para ele, depois eu
o joguei em uma função recursiva que pegava o caracter e jogava um para frente
cptr + 1, e depois ele printava o caracter no final da recursividade*/

//EX 7 ---------------------------------------
//Aqui eu declaro as variaveis t e te que serao quantos produtos deveram ser cadastrados
int t,te;
// input do usuario para t
printf("\n\n\nDigite quantos produtos deseja cadastrar: ");
scanf("%d",&t);
//atribui o te a t para a função Listar
te = t;
// Inicializa a estrutura e aloca a sua memoria
struct Estoque *e = (struct Estoque *)malloc(t * sizeof(struct Estoque));
// chama a função recursiva para realizar os inputs da estrutura
Contar(&t,e, 0);
// chama a função recursiva para realizar a listagem da estrutura
Listar(te,e,0);
// libera a memoria
free(e);
/*Neste exercicio eu criei um estoque que lista os produtos apos o cadastro, eu utilizei duas funçoes recusivas,
uma para realizar os inputs dentro da estrutura, levando em conta o tamanho definido pelo usuario e a outra 
realiza os print dos resultados */


//Ex 8 ----------------------------------------
//Declaração de n2 o tamanho de vet
int n2;
// input de n2
printf("\nDigite um numero para o vetor : ");
scanf("%d",&n2);
// declaração de vet e sua alocação de memoria
int *vet = (int *)malloc(n * sizeof(int));
//acionamento da função popular
popular(n2,vet,0);
printf("Vetores dentro de vet: ");
//acionamento da função imprimir
imprimir(n2,vet, 0);
// liberação de memoria
free(vet);
/*Neste exercicio eu fiz com ponteiro uma inserção de dados em um vetor, e imprimi eles, eu declarei a variavel
de tamanho do vetor e um input para tal, depois eu declarei o vetor e alocando memoria para o mesmo, depois eu crie uma 
função recursiva para povoar o vetor e outra para imprimi-lo*/

//Ex 9 ----------------------------------------
//Declara a variavel m e n como int
int m2, n3;
// inputs de m e n, sendo linha e coluna respectivamente
printf("\n\nDigite o número de linhas : ");
scanf("%d", &m2);
printf("Digite o número de colunas: ");
scanf("%d", &n3);
//declara a matriz e aloca a memoria dinamicamente
int **matriz = (int **)malloc(m2 * sizeof(int *));
for (int i = 0; i < m2; i++) {
    matriz[i] = (int *)malloc(n3 * sizeof(int));}
// preenche a matriz com inputs
preencher(matriz, m2, n3, 0, 0);
printf("\nMatriz preenchida:\n");
//imprime a matriz bonitinha 
imprimir_matriz(matriz, m2, n3, 0, 0);
//for para liberar memoria
for (int i = 0; i < m2; i++) {
    free(matriz[i]);}
/* Neste exercicio eu criei duas variaveis que que pelo input eu adicionava o tamanho de linhas e colunas, e depois eu
declarava a matriz e utilizava uma função para alocar a memoria linha por linha da matriz conforme o tamanho inputad, depois 
eu inputei por outra função recursiva os valores da matriz, e utilizei outra função recursiva para imprimir a matriz, depois eu 
liberei a memoria com uma quarta função, que liberava a memoria linha por linha e depois da matriz em si
OBS: este exercicio foi mais complicadinho para alocar a matriz em si, mas deu tudo certo! */
return (0);
}
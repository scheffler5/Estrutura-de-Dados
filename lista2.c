#include <stdio.h> 
#include <stdlib.h>
/*
EX 1 - 
Incrementa o proximo elemento da memoria, se for char +1byte e int +2bytes
p++;      
Incrementa o proximo valor da posição de p, por exemplo de for um int 1 ele vai para 2
• (*p)++;         
Ele acessa o valor do ponteiro e depois incrementa
• *(p++); 
Ele acessa o pronteiro em uma posição especifica como 10, quando um vetor seria p[10]
• O que quer dizer *(p+10);
*/


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



int main()  { 
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



return (0);
}
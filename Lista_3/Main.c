#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include <string.h>
#include <ctype.h>

#define TAMANHO_PILHA 4
int main(){
    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Pilha* p4 = cria_Pilha();
    Pilha* piii = cria_Pilha();
    Pilha* pi = cria_Pilha(); 
    Pilha* pii = cria_Pilha();
    Pilha* p5 = cria_Pilha();
    int i;
    for(i=0; i < 4; i++)
        insere_Pilha(pi,a[i]);

    for(i=0; i < 4; i++)
        remove_Pilha(pi);



    for(i=0; i < 4; i++)
        insere_Pilha(pi,a[i]);

//EX 1 Função pop2 para remover da pilha com um for 
    pop2(pi,2);
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));
//Função push2 para adicionar na pilha com um for 
    push2(pi,a[0],2);
    imprime_Pilha(pi);
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));
    //EX 2, neste exercicio eu apenas reutilizei o pop2 do exercicio colocanco o n como input
    int n;
    printf("Digite um Numero para n :");
    scanf("%d",&n);
    pop2(pi,n);
    imprime_Pilha(pi);
    printf("Tamanho: %d\n\n\n\n",tamanho_Pilha(pi));

    transferir(pi);
    int tamanho, maior ,menor ,media,t2;
    printf("Digite um Numero para n :");
    scanf("%d",&tamanho);
    numeros(pii,tamanho);
    printf("Digite um Numero para n :");
    scanf("%d",&t2);
    push3(piii,t2);
    verificar(pii, piii);
    par(pii);
    impar(pii);

    char str[100];
    push4(p4,str);
    imprime_Pilha3(p4);

    if (Palindromo(p4, str)) {
        printf("É um palíndromo!\n");
    } else {
        printf("Não é um palíndromo.\n");
    }


    int opcao = -1, valor, n3;
    do{
        
        switch (opcao) {
            menu();
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            case 1:
                if (vazia(p5)) {
                    printf("A pilha está vazia.\n");
                } else {
                    printf("A pilha não está vazia.\n");
                }
                break;
            case 2:
                cheia(p5);
                break;
            case 3:
                printf("Digite quantos valores deseja empilhar: ");
                scanf("%d", &n3);
                empilhar(p5, n3);
                imprime_Pilha3(p5);
                break;
            case 4:
                printf("Digite quantos valores deseja desempilhar: ");
                scanf("%d", &n3);
                desempilhar(p5, n3);
                imprime_Pilha3(p5);
                break;
            case 5:
                topo(p5);
                break;
            case 7:
                printf("Saindo...\n");
                return 0;
            case 6:
                libera_Pilha(p5);
                printf("Pilha Liberada!");
            default:
                printf("Opção inválida!\n");
        }
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
    }while (opcao != 7);
    
    libera_Pilha(p5);
    libera_Pilha(p4);
    libera_Pilha(pii);
    libera_Pilha(piii);
    libera_Pilha(pi);
    system("pause");
    
    return 0;
}


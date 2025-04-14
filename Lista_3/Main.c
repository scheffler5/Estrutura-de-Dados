#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
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

    push4(p4);
    imprime_Pilha3(p4);
    

    libera_Pilha(piii);
    libera_Pilha(pi);
    system("pause");
    
    return 0;
}


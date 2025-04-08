#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

int main() {
    Pilha *p = cria_Pilha();

    struct aluno a[4] = {
        {2, "Andre", 9.5, 7.8, 8.5},
        {4, "Ricardo", 7.5, 8.7, 6.8},
        {1, "Bianca", 9.7, 6.7, 8.4},
        {3, "Ana", 5.7, 6.1, 7.4}
    };

    struct aluno saida[4];


    push2(p, a, 2);


    pop2(p, saida, 2);

    int quantidade;
    printf("Digite a quantidade que deverá ser empilhada: ");
    scanf("%d",&quantidade);
    push2(p, a, quantidade);
    pop2(p, saida, quantidade);


    
    return 0;
}

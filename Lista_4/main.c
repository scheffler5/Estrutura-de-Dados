#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"

int main(){
    struct aluno al, a[4] = {{2,"Andre",9.5,7.8,8.5},
                             {4,"Ricardo",7.5,8.7,6.8},
                             {1,"Bianca",9.7,6.7,8.4},
                             {3,"Ana",5.7,6.1,7.4}};
    Fila* fi = cria_Fila();
    printf("Tamanho: %d\n\n\n\n", tamanho_Fila(fi));
    
    // Inserindo alunos na fila
    int i;
    for(i = 0; i < 4; i++) {
        insere_Fila(fi, a[i]);
        if(Fila_vazia(fi)) {
            printf("Erro!!!!!!\n");
        }

        consulta_Fila(fi, &al);
        printf("Consulta: %d \t %s\n", al.matricula, al.nome);
    }

    imprime_Fila(fi);
    printf("Tamanho: %d\n\n\n\n", tamanho_Fila(fi));

    // Removendo alunos da fila
    for(i = 0; i < 4; i++) {
        remove_Fila(fi);
        consulta_Fila(fi, &al);
        printf("Consulta: %d \t %s\n", al.matricula, al.nome);
    }
    printf("Tamanho: %d\n\n\n\n", tamanho_Fila(fi));
    imprime_Fila(fi);

    // Reenfileirando alunos
    for(i = 0; i < 4; i++) {
        insere_Fila(fi, a[i]);
    }

    printf("Tamanho: %d\n\n\n\n", tamanho_Fila(fi));
    imprime_Fila(fi);

    Fila* f1 = cria_Fila();
    Fila* f2 = cria_Fila();

    // Separando a fila com base na matrícula
    if (separa(fi, f2, 2)) {
        printf("Separação feita com sucesso!\n");
        printf("Fila 1:\n");
        imprime_Fila(fi);
        printf("Fila 2:\n");
        imprime_Fila(f2);
    } else {
        printf("Não foi possível separar. Matrícula não encontrada.\n");
    }

    // Trabalhando com a fila e pilha para inverter a fila
    Fila* f = cria_Fila();

    for(i = 0; i < 4; i++) {
        insere_Fila(f, a[i]);
        if(Fila_vazia(f)) {
            printf("Erro!!!!!!\n");
        }}
    

    printf("Fila original:\n");
    imprime_Fila(f);

    // Invertendo a fila
    inverterFila(f);

    printf("Fila invertida:\n");
    imprime_Fila(f);



    Fila* fiii = cria_Fila();
    for(i = 0; i < 3; i++) {
        FuraFila(fiii, a[i]);
        if(filaVaziaa(fiii)) {
            printf("Erro!!!!!!\n");
        }}



    printf("Fila após inserções com FuraFila:\n");
    percorrerFila(fiii);

    for(i = 0; i < 3; i++) {
        FuraFila(fiii, a[i]);
        if(filaVaziaa(fiii)) {
            printf("Erro!!!!!!\n");
        }}

    printf("Fila após mais inserções:\n");
    percorrerFila(fiii);

    printf("Fila após remoção do primeiro item:\n");
    percorrerFila(fiii);
    

    libera_Fila(fiii);
    libera_Fila(fi);
    libera_Fila(f1);
    libera_Fila(f2);
    system("pause");
    return 0;
}


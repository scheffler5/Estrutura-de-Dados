#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    // EX 1 - Separando a fila em duas filas
    printf("Separando a fila em duas filas...\n");
    if (separa(fi, f2, 2)) {
        printf("Separação feita com sucesso!\n");
        printf("Fila 1:\n");
        imprime_Fila(fi);
        printf("Fila 2:\n");
        imprime_Fila(f2);
    } else {
        printf("Não foi possível separar. Matrícula não encontrada.\n");
    }

    //  EX 3 - Invertendo a fila
    printf("Inversão da fila...\n");
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


    // EX 4 - FuraFila
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
    


    //EX 5 - Aviao
    menu();

    
    //EX6 -merge de filas
    Fila* f5 = cria_Fila(); 
    Fila* f6 = cria_Fila();
    Fila* resultado = cria_Fila();

    emfilera(f5, 1);
    emfilera(f5, 4);
    emfilera(f5, 6);


    emfilera(f6, 2);
    emfilera(f6, 3);
    emfilera(f6, 5);
    emfilera(f6, 7);

    mergeFilas(f5, f6, resultado);
    printf("Resultado do merge:\n");
    imprime_Fila(resultado);

    libera_Fila(fiii);
    libera_Fila(fi);
    libera_Fila(f1);
    libera_Fila(f2);
    system("pause");
    return 0;
}


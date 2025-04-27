#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h"


int main(){
    struct aluno al,a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Fila* fi = cria_Fila();
    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));
    int i;
    for(i=0; i < 4; i++){
        insere_Fila(fi,a[i]);
        if(Fila_vazia(fi))
            printf("Erro!!!!!!\n");

        consulta_Fila(fi,&al);
        printf("Consulta: %d \t %s\n",al.matricula,al.nome);
    }

    imprime_Fila(fi);
    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));

    for(i=0; i < 4; i++){
        remove_Fila(fi);
        consulta_Fila(fi,&al);
        printf("Consulta: %d \t %s\n",al.matricula,al.nome);
    }
    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));
    imprime_Fila(fi);

    for(i=0; i < 4; i++)
        insere_Fila(fi,a[i]);

    printf("Tamanho: %d\n\n\n\n",tamanho_Fila(fi));
    imprime_Fila(fi);

    Fila* f1 = cria_Fila();
    Fila* f2 = cria_Fila();

// inserir vários alunos na f1 normalmente

// Agora queremos dividir depois da matrícula 2:
    if (separa(fi, f2, 2)) {
        printf("Separação feita com sucesso!\n");
        printf("Fila 1:\n");
        imprime_Fila(fi);
        printf("Fila 2:\n");
        imprime_Fila(f2);
    } else {
        printf("Não foi possível separar. Matrícula não encontrada.\n");
    }

    


    libera_Fila(fi);
    system("pause");
    return 0;
}



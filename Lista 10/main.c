#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include <limits.h> // Para usar INT_MAX
#include <stdbool.h> // Para usar o tipo bool

int main(){
    int eh_digrafo = 1;
    Grafo* gr = cria_Grafo(5, 5, 0);

    insereAresta(gr, 0, 1, eh_digrafo, 0);
    insereAresta(gr, 1, 3, eh_digrafo, 0);
    insereAresta(gr, 1, 2, eh_digrafo, 0);
    insereAresta(gr, 2, 4, eh_digrafo, 0);
    insereAresta(gr, 3, 0, eh_digrafo, 0);
    insereAresta(gr, 3, 4, eh_digrafo, 0);
    insereAresta(gr, 4, 1, eh_digrafo, 0);

    imprime_Grafo(gr);
    printf("\nBusca \n");

    libera_Grafo(gr);

    system("pause");
    return 0;
}

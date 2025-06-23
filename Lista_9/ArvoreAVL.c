#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h" //inclui os Prot�tipos

struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        //printf("%d\n",(*raiz)->info);
        //printf("No %d: %d\n",(*raiz)->info,fatorBalanceamento_NO(*raiz));
        printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz));
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *raiz){//LL
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*raiz)->esq;
    (*raiz)->esq = B->dir;
    B->dir = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*raiz)->altura) + 1;
    *raiz = B;
}


void RotacaoLR(ArvAVL *raiz){//LR
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL *raiz){//RL
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res;
    if(*raiz == NULL){//�rvore vazia ou n� folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor n�o existe
	    printf("valor n�o existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// n� tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // n� tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

/*Neste exercicio 4, é pedido a rotação RR, como o professor ja havia passado a rotação LL, e a mesma é o inverso da LL, apenas foi mudado de esq para dir e vice e versa, entretanto,
A lógica da operação consiste em, primeiramente, eleger um pivô – que chamaremos de B – correspondente à subárvore direita da raiz desbalanceada. A seguir, ocorre a reorganização dos 
vínculos: a subárvore que estava à esquerda de B passa a ocupar a posição de filho direito da raiz original. Subsequentemente, a própria raiz original se torna a subárvore esquerda de B. 
Com a estrutura devidamente rotacionada, as alturas dos dois nós principais envolvidos são recalculadas para refletir a nova configuração. Para finalizar, B é designado como a nova raiz 
desta subárvore, garantindo que o equilíbrio seja restabelecido
*/
void RotacaoRR(ArvAVL *raiz){//LL
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*raiz)->dir;
    (*raiz)->dir = B->esq;
    B->esq = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->dir),altura_NO((*raiz)->esq)) + 1;
    B->altura = maior(altura_NO(B->dir),(*raiz)->altura) + 1;
    *raiz = B;}


/*No Exercicio 5- 
A função primordial de inserção opera recursivamente, recebendo como parâmetros um ponteiro para o nó raiz da (sub)árvore e o valor a ser inserido. 
A sua lógica inicia-se com a verificação da condição de base: se o ponteiro da árvore for nulo, um novo nó é alocado dinamicamente, o valor é armazenado e 
este novo nó é retornado. Caso a árvore não seja vazia, a função compara o valor de entrada com o valor do nó atual. Se o valor for menor, a função é invocada 
recursivamente para a subárvore esquerda; se for maior, a chamada recursiva prossegue para a subárvore direita. Na eventualidade de os valores serem iguais, a 
operação é concluída retornando o nó sem modificação, prevenindo a inserção de duplicatas.

O mecanismo de auto-balanceamento é ativado durante o desempilhamento recursivo, ou seja, após o ponto de inserção ter sido encontrado e a recursão começar a retornar. 
Em cada nível de retorno, é realizada uma verificação do fator de balanceamento do nó corrente. Se o valor absoluto deste fator for igual ou superior a 2, significa que a 
propriedade da árvore AVL foi violada. Neste momento, a rotina de rotação adequada é acionada para reestruturar a subárvore e corrigir o desequilíbrio. Este processo de verificação 
e ajuste é repetido sucessivamente em cada nó ancestral no caminho de volta à raiz. Ao final de cada etapa recursiva, a altura do nó atual é recalculada e atualizada.


*/

/* Exercicio 6

A função de remoção AVL opera recursivamente para localizar e excluir um nó-alvo, tratando os casos de zero, um ou dois filhos, sendo que neste último utiliza uma função 
procuraMenor para achar seu sucessor. Ao retornar das chamadas recursivas, o algoritmo recalcula a altura dos nós e verifica o fator de balanceamento em cada etapa do caminho 
de volta à raiz. Se um desequilíbrio for detectado, as funções de rotação são imediatamente executadas para restaurar o invariante da árvore, garantindo assim a sua correta e 
balanceada estrutura.



*/

int arvoreEhBalanceada(ArvAVL no) {
    if (no == NULL) return 1;
    if (abs(fatorBalanceamento_NO(no)) > 1) return 0;
    return arvoreEhBalanceada(no->esq) && arvoreEhBalanceada(no->dir);}

/*Ex 7 -
A validação de uma árvore binária como sendo AVL se baseia em um princípio recursivo fundamental: para uma árvore ser considerada AVL, 
três condições devem ser simultaneamente verdadeiras para todos os nós que a compõem. Primeiro, o fator de balanceamento do nó atual deve 
estar estritamente no intervalo de [-1, 1]. Segundo, sua subárvore esquerda deve ser, em si, uma árvore AVL completa. Terceiro, sua subárvore 
direita também deve satisfazer todas as propriedades de uma árvore AVL.

A função, portanto, percorre a árvore e, para cada nó, avalia essas três condições. A verificação para ao encontrar a primeira violação, 
retornando um indicativo de falha (falso). A condição de parada da recursão ocorre ao se atingir um nó nulo (uma folha não existente), que por 
definição é considerado uma estrutura AVL válida. A árvore inteira só será classificada como AVL se, e somente se, todos os seus nós passarem por 
essa rigorosa verificação tripla.

*/


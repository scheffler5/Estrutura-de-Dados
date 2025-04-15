//Arquivo PilhaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Pilha;
struct numero{
    int nume;
};
Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);
int push2(Pilha* p, struct aluno a, int n);
int pop2(Pilha* pi,int n);
void transferir(Pilha* pi);
int numeros(Pilha* pii, int n);
void imprime_Pilha2(Pilha* pii);
int push3 (Pilha* pi,int n);
int verificar(Pilha* pii, Pilha* piii);
int push4(Pilha* pi,char* str);
void imprime_Pilha3(Pilha* pi);
int Palindromo(Pilha* pi, char* str);
int par(Pilha* pi);
int impar(Pilha* pi);
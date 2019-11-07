#define TRUE 1
#define FALSE 0

//#include <macth.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
        int id;
        char nome[15];  //CAMINHO DA COR
}memoria;

//FILA DE CORES PARA SORTEIO
struct no{
    int dado;
    struct no *prox;
};

typedef struct{
    struct no *inicio;
    struct no *fim;
}fila;


void criarFila(fila *f)
{
    f->inicio=NULL;
    f->fim=NULL;
}

int inserirNaFila(fila *q, int d)
{
    struct no *aux;
    aux = (struct no*)malloc(sizeof(struct no));
    if (aux==NULL)
        return (FALSE);

    aux->dado=d;
    aux->prox=NULL;

    if (q->inicio==NULL)
        q->inicio=aux;
    if (q->fim!=NULL)
        q->fim->prox=aux;

    q->fim=aux;
    return(TRUE);
}

int removerDaFila(fila *q, int *d)
{
    struct no *aux;
    if (q->inicio==NULL)
        return (FALSE);

    aux=q->inicio;
    q->inicio=aux->prox;
    if (q->inicio == NULL)
        q->fim = NULL;

    *d=aux->dado;
    free(aux);
    return(TRUE);
}

void imprimirFila (fila q)
{
    struct no *aux;

    aux=q.inicio;

    if(q.inicio==NULL)
    {
        printf("Nao existem cores sorteadas");
    }

    printf("\n");

    while(aux!=NULL)
    {
        printf("\nNUMEROS: %d\n",aux->dado);
        aux=aux->prox;
    }
}

//VERIFICA SE A COR CLICADA ESTA CORRETA
int verificaSequencia(fila q, int id)
{
    struct no *aux;

    aux=q.inicio;

    if(q.inicio==NULL)
    {
        printf("A FILA ESTA VAZIA");
    }

    printf("\n");

    if((aux->dado)==id){
            printf("OK: %d\n",aux->dado);
            return(TRUE);
        }else
            return(FALSE);

        aux=aux->prox;

}

//VERIFICA SE A FILA ESTA VAZIA
int isEmpty(fila q)
{
    if (q.inicio==NULL)
        return (TRUE);
    else
        return (FALSE);
}

//FIM DAS FUNÇÕES DA FILA DE CORES

//SOMA OS PONTOS DAS FASES
int pontuacao(int vetorPontos[]){
    int totalPontos = 0, i;

    for(i=0;i<8;i++){
        totalPontos += vetorPontos[i];
    }
    return totalPontos;
}

//REMOVE DE UMA FILA E INSERE NA OUTRA
void trocarFila(fila f1,fila f2, int idCor){
    while(!isEmpty(f1))
    {
        removerDaFila(&f1,&idCor);
        //printf("\nremovido: %d\n",idCor);
        inserirNaFila(&f2,idCor);
        //printf("\ninserido: %d\n",idCor);
    }
}



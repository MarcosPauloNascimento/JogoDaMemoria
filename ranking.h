#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>

//LISTA ORDENADA DE RANKING

typedef struct{
        char nome[10];  //NOME DO JOGADOR
        int record;  //TOTAL DE PONTOS
}jogada;

struct nolista{
    jogada dado;
    struct nolista *prox;
};

typedef struct{
    struct nolista *inicio;
}listaRanking;


void criarLista(listaRanking *q)
{
    q->inicio=NULL;
}

int inserirNaLista(listaRanking *q, jogada j)
{
    struct nolista *aux, *atual, *anterior;
    aux = (struct nolista *) malloc(sizeof(struct nolista));
    if (aux!=NULL){
        aux->dado = j;
        aux->prox = NULL;
        anterior = NULL;
        atual = q->inicio;

        while (atual != NULL && j.record < atual->dado.record){
            anterior = atual;
            atual = atual->prox;
        }
        if (anterior == NULL){
            aux->prox = q->inicio;
            q->inicio = aux;
        }else{
            anterior->prox = aux;
            aux->prox = atual;
        }
    }
}

void imprimirLista (listaRanking q)
{
    char record[10], pos[3];
    int x=33, x1=70, x2=240, y=200, n=1;
    struct nolista*aux;
    aux = q.inicio;
    if (aux != NULL){
        do{
            //printf("Record: %d - Nome: %s\n\n", aux->dado.record, aux->dado.nome);
            itoa(aux->dado.record,record,10);
            itoa(n,pos,10);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(x,y,pos);
            outtextxy(x1,y,aux->dado.nome);
            outtextxy(x2,y,record);
            aux = aux->prox;
            y+=30;
            n+=1;
        }while (aux != NULL && y<=470);
    }
}

int isEmpty(listaRanking q)
{
    if (q.inicio==NULL)
        return TRUE;
    else
        return FALSE;
}


